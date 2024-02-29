#include <vector>
#include <string>
#include <boost/date_time/gregorian/parsers.hpp>
#include "Price.h"

Price Price::PriceNotFound = Price();

Price::Price(std::string csvValues)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(csvValues);

    while (std::getline(stream, token, ','))
    {
        tokens.push_back(token);
    }

    if (tokens.size() != 7)
    {
        std::cout << "Could not parse price data: " << csvValues;
        date = boost::gregorian::date(boost::gregorian::not_a_date_time);
    }
    else
    {
        date = boost::gregorian::from_string(tokens[0]);
        open = std::stod(tokens[1]);
        high = std::stod(tokens[2]);
        low = std::stod(tokens[3]);
        close = std::stod(tokens[4]);
        adjClose = std::stod(tokens[5]);
        volume = std::stod(tokens[6]);
    }
}
