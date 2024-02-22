#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include "Price/PriceSource.h"
#include "Portfolio/Portfolio.h"

std::string GenerateCsvPortfolioValuation(const boost::gregorian::date &date);

int main() {
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    boost::gregorian::date twenty07 = boost::gregorian::date(2007, 02, 17);
    std::string csvValues = GenerateCsvPortfolioValuation(today);
    std::cout << csvValues;
}

std::string GenerateCsvPortfolioValuation(const boost::gregorian::date &date) {
    auto portfolio = PortfolioFactory::createFromCsv(
            "D:\\Scratch\\Positions\\positions.csv",
            date);
    auto csvValues = portfolio->GetCsvFormat(date);
    return csvValues;
}
