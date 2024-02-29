#ifndef PORTFOLIOVIEWER_POSITION_H
#define PORTFOLIOVIEWER_POSITION_H

#include <unordered_map>
#include "../Price/PriceSource.h"

class Position {
public:
    Position(const std::string &ticker,
             const std::string &type,
             const std::string &liquidityType,
             const std::string &priceSourceName,
             const boost::gregorian::date &date,
             const std::shared_ptr<IPriceSource> &priceSource,
             double quantity,
             std::string changeTypeString,
             double multiplier,
             const std::string &comment);

    enum class ChangeType {
        Buy,
        Sell,
        Dividend
    };

    std::shared_ptr<IPriceSource> priceSource;
    double quantity;
    ChangeType changeType;
    std::string ticker;
    std::string type;
    std::string liquidityType;
    std::string priceSourceName;
    boost::gregorian::date date;
    double multiplier;
    std::string comment;

    std::future<double> GetPriceAsync(const boost::gregorian::date &date);
    std::string convertChangeType(ChangeType changeType);

private:
    static const std::unordered_map<std::string, ChangeType> changeTypeMap;
    ChangeType convertChangeType(const std::string &changeType);
};

#endif