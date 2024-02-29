#include <fstream>
#include <unordered_map>
#include "Portfolio.h"
#include "../Price/PriceSourceFactory.h"
#include <boost/algorithm/string.hpp>

Portfolio::Portfolio(const std::vector<std::shared_ptr<Position>> &positions) : positions(positions) {}

const std::vector<std::string> Portfolio::inputColumns = {"Date","Ticker","Type","Liquidity Type","Price Source","Quantity"};
const std::vector<std::string> Portfolio::optionalInputColumns = {"Multiplier", "Comment"};
const std::vector<std::string> Portfolio::generatedColumns = {"Price","Value"};

std::string Portfolio::GetCsvFormat(const boost::gregorian::date& date)
{
    std::ostringstream stream;
    stream << boost::algorithm::join(inputColumns, ",") << ","
        << boost::algorithm::join(optionalInputColumns, ",") << ","
        << boost::algorithm::join(generatedColumns, ",") << std::endl;
    for (auto position : positions)
    {
        auto futurePrice = position->GetPriceAsync(date);
        double price = futurePrice.get(); // This blocks until the future is ready
        stream << to_iso_extended_string(date)
                << "," << position->ticker
                << "," << position->type
                << "," << position->liquidityType
                << "," << position->priceSourceName
                << "," << position->quantity
                << "," << position->multiplier
                << "," << position->comment
                << "," << price
                << "," << price * position->quantity
                << std::endl;
    }
    return stream.str();
}

std::shared_ptr<Portfolio> PortfolioFactory::createFromCsv(
        const std::string & filePath,
        const boost::gregorian::date & date)
{
    std::vector<std::string> lines;
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::ostringstream error;
        error << "Could not open " << filePath;
        throw new std::exception(error.str().c_str());
    }

    std::string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    return createFromCsvFileContents(lines, date);
}

std::shared_ptr<Portfolio> PortfolioFactory::createFromCsvFileContents(const std::vector<std::string> & contents, const boost::gregorian::date & date, bool hasHeaders)
{
    size_t offset = hasHeaders ? 1 : 0;
    std::unordered_map<std::string, std::shared_ptr<Position>> positionsMap;
    auto expectedColumns = Portfolio::inputColumns.size();
    auto expectedColumnsWithOptional = expectedColumns + Portfolio::optionalInputColumns.size();
    for (auto i = offset; i < contents.size(); ++i)
    {
        std::vector<std::string> cols;
        boost::algorithm::split(cols, contents[i], boost::is_any_of(","));
        auto numberOfColumns = cols.size();
        if (numberOfColumns < expectedColumns || numberOfColumns > expectedColumnsWithOptional)
        {
            std::ostringstream error;
            error << "Incorrect number of columns in positionsMap file. Should be between "
            << expectedColumns << " and " << expectedColumnsWithOptional << " but there are "
                    << cols.size()
                    << "."
                    << std::endl
                    << "Full text: "
                    << contents[i];
            std::cout << error.str().c_str() << std::endl;
            continue;
        }
        auto posDate = boost::gregorian::from_string(cols[0]);
        if (posDate <= date)
        {
            auto ticker = cols[1];
            auto existingPos = positionsMap.find(ticker);
            auto candidateNewPos = std::make_shared<Position>(
                    cols[1],
                    cols[2],
                    cols[3],
                    cols[4],
                    posDate,
                    PriceSourceFactory::Create(cols[4], cols[1]),
                    std::stod(cols[5]),
                    numberOfColumns > expectedColumns ? std::stod(cols[6]) : 1,
                    numberOfColumns == expectedColumnsWithOptional ? cols[7] : "");

            if (existingPos == positionsMap.end())
            {
                positionsMap[ticker] = candidateNewPos;
            }
            else
            {
                if (candidateNewPos->date > existingPos->second->date)
                {
                    positionsMap[ticker] = candidateNewPos;
                }
            }
        }
    }

    std::vector<std::shared_ptr<Position>> positions;
    std::transform(
            positionsMap.begin(),
            positionsMap.end(),
            std::back_inserter(positions),
            [](const auto & pair) { return pair.second; } );
    return std::make_shared<Portfolio>(positions);
}
