#ifndef PORTFOLIOVIEWER_PRICE_H
#define PORTFOLIOVIEWER_PRICE_H

#include <iostream>
#include <utility>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/formatters.hpp>

class Price {
public:
    boost::gregorian::date date;
    double open;
    double high;
    double low;
    double close;
    double adjClose;
    double volume;

    Price(boost::gregorian::date date, double open, double high, double low, double close, double adjClose, double volume)
            : date(std::move(date)), open(open), high(high), low(low), close(close), adjClose(adjClose), volume(volume) {}

    Price(boost::gregorian::date date, double adjClose)
            : date(std::move(date)), open(adjClose), high(adjClose), low(adjClose), close(adjClose), adjClose(adjClose), volume(0) {}

    Price(std::string csvValues);

    Price() : date(boost::gregorian::date(boost::gregorian::not_a_date_time)), open(0), high(0), low(0), close(0), adjClose(0), volume(0) {}

    static Price PriceNotFound;

    void print() const {
        std::cout << "Date: " << boost::gregorian::to_simple_string(date) << ", Open: " << open << ", High: " << high
                  << ", Low: " << low << ", Close: " << close << ", Adj Close: " << adjClose
                  << ", Volume: " << volume << std::endl;
    }
};

#endif //PORTFOLIOVIEWER_PRICE_H
