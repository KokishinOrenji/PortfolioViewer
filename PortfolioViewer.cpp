#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include "Price/PriceSource.h"
#include "Portfolio/Portfolio.h"

int main() {
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    auto portfolio = PortfolioFactory::createFromCsv("D:\\Scratch\\Positions\\positions.csv");
    auto csvValues = portfolio->GetCsvFormat(today);
    std::cout << csvValues;
    //std::cout << to_iso_string(today) << std::endl;

/*
    auto webRequest = std::make_shared<WebRequest>("G:/Program Files/Git/mingw64/etc/ssl/certs/ca-bundle.crt", true);
    auto arbPriceSource = std::make_shared<YahooPriceSource>("ARB.L", webRequest);
    auto btcPriceSource = std::make_shared<YahooPriceSource>("BTC-GBP", webRequest);
    auto date = std::make_shared<boost::gregorian::date>(2024, 2, 5);
    auto arbPriceFuture = arbPriceSource->GetPriceAsync(*date);
    auto btcPriceFuture = btcPriceSource->GetPriceAsync(*date);
    auto arbPrice = arbPriceFuture.get();
    auto btcPrice = btcPriceFuture.get();
*/
}
