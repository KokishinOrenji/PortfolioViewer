#include <fstream>
#include "Portfolio.h"
#include "../Price/PriceSourceFactory.h"
#include <boost/algorithm/string.hpp>

Portfolio::Portfolio(const std::vector<std::shared_ptr<Position>> &positions) : positions(positions) {}

const std::vector<std::string> Portfolio::inputColumns = {"Ticker","Type","Liquidity Type","Price Source","Quantity"};
const std::vector<std::string> Portfolio::generatedColumns = {"Price","Value"};

std::string Portfolio::GetCsvFormat(const boost::gregorian::date& date)
{
    std::ostringstream stream;
    stream << boost::algorithm::join(inputColumns, ",") << ","
        << boost::algorithm::join(generatedColumns, ",") << std::endl;
    for (auto position : positions)
    {
        auto futurePrice = position->GetPriceAsync(date);
        double price = futurePrice.get(); // This blocks until the future is ready
        stream << position->ticker
               << "," << position->type
               << "," << position->liquidityType
               << "," << position->quantity
               << "," << position->priceSourceName
               << "," << price * position->quantity
               << std::endl;
    }
    return stream.str();
}

std::shared_ptr<Portfolio> PortfolioFactory::createFromCsv(const std::string & filePath)
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

    return createFromCsvFileContents(lines);
}

std::shared_ptr<Portfolio> PortfolioFactory::createFromCsvFileContents(const std::vector<std::string> & contents, bool hasHeaders)
{
    size_t offset = hasHeaders ? 1 : 0;
    std::vector<std::shared_ptr<Position>> positions;
    for (auto i = offset; i < contents.size(); ++i)
    {
        std::vector<std::string> cols;
        boost::algorithm::split(cols, contents[i], boost::is_any_of(","));
        if (cols.size() != 5)
        {
            std::ostringstream error;
            error << "Incorrect number of columns in positions file. Should be 5, but there is "
                    << cols.size()
                    << "."
                    << std::endl
                    << "Full text: "
                    << contents[i];
            std::cout << error.str().c_str() << std::endl;
            continue;
        }
        positions.push_back(std::make_shared<Position>(cols[0], cols[1], cols[2],cols[3],
                                                        PriceSourceFactory::Create(cols[3], cols[0]),
                                                        std::stod(cols[4])));
    }

    return std::make_shared<Portfolio>(positions);
}
