#ifndef PORTFOLIOVIEWER_POSITION_H
#define PORTFOLIOVIEWER_POSITION_H

#include "../Price/PriceSource.h"

class Position {
public:
    Position(const std::string &ticker,
             const std::string &type,
             const std::string &liquidityType,
             const std::string &priceSourceName,
             const boost::gregorian::date& date,
             const std::shared_ptr<IPriceSource> &priceSource,
             double quantity);

    std::shared_ptr<IPriceSource> priceSource;
    double quantity;
    std::string ticker;
    std::string type;
    std::string liquidityType;
    std::string priceSourceName;
    boost::gregorian::date date;

    std::future<double> GetPriceAsync(const boost::gregorian::date& date);
};
#endif