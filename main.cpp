#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include "Price/PriceSource.h"
#include "Portfolio/Portfolio.h"

int main() {
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    auto portfolio = PortfolioFactory::createFromCsv("D:\\Scratch\\Positions\\positions.csv");
    auto csvValues = portfolio->GetCsvFormat(today);
    std::cout << csvValues;
}
