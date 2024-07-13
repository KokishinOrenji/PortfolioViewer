#include <boost/date_time/gregorian/gregorian.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xview.hpp>
#include <iostream>
#include "Price/PriceSource.h"
#include "Portfolio/Portfolio.h"

std::string GenerateCsvPortfolioValuation(const boost::gregorian::date &date);


int main() {
    boost::gregorian::date twenty07 = boost::gregorian::date(2007, 02, 17);
    boost::gregorian::date fifteenthFeb2024 = boost::gregorian::date(2024, 02, 15);
    boost::gregorian::date wednesday = boost::gregorian::date(2024, 02, 21);
    boost::gregorian::date monthAgo = boost::gregorian::date(2024, 5, 7);
    boost::gregorian::date monthsAgo = boost::gregorian::date(2024, 4, 1);
    //boost::gregorian::date today = boost::gregorian::date(2024, 7, 5);
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();

    std::string csvValues = GenerateCsvPortfolioValuation(monthsAgo);
    std::cout << csvValues;
    csvValues = GenerateCsvPortfolioValuation(today);
    std::cout << csvValues;
    return 0;
}

std::string GenerateCsvPortfolioValuation(const boost::gregorian::date &date) {
    auto portfolio = PortfolioFactory::createFromCsv(
            "D:\\Scratch\\Positions\\positions.csv",
            date);
    auto csvValues = portfolio->GetCsvFormat(date);
    return csvValues;
}

