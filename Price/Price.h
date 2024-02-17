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

    // You can add more functions here if needed, like a function to print the data
    void print() const {
        std::cout << "Date: " << boost::gregorian::to_simple_string(date) << ", Open: " << open << ", High: " << high
                  << ", Low: " << low << ", Close: " << close << ", Adj Close: " << adjClose
                  << ", Volume: " << volume << std::endl;
    }
};

#endif //PORTFOLIOVIEWER_PRICE_H
