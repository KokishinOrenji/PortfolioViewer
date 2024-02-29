#include "Position.h"

Position::Position(
        const std::string &ticker,
        const std::string &type,
        const std::string &liquidityType,
        const std::string &priceSourceName,
        const boost::gregorian::date& date,
        const std::shared_ptr<IPriceSource> &priceSource,
        double quantity,
        std::string changeTypeString,
        double multiplier,
        const std::string & comment)
        : priceSource(priceSource),
          quantity(quantity), ticker(ticker),
          type(type),
          liquidityType(liquidityType),
          priceSourceName(priceSourceName),
          date(date),
          multiplier(multiplier),
          comment(comment) {
    changeType = convertChangeType(changeTypeString);
}

std::future<double> Position::GetPriceAsync(const boost::gregorian::date& date) {
    return std::async(std::launch::async, [this, date]() -> double {
       auto price = priceSource->GetPriceAsync(date);
        return price.get().adjClose * multiplier;
    });
}

enum Position::ChangeType Position::convertChangeType(const std::string & changeType) {
    auto it = changeTypeMap.find(changeType);
    if (it != changeTypeMap.end()) {
        return it->second;
    }
    return ChangeType::Buy;
}

std::string Position::convertChangeType(ChangeType changeType) {
    for (const auto & pair: changeTypeMap) {
        if (pair.second == changeType) {
            return pair.first;
        }
    }
    return "B";
}

const std::unordered_map<std::string, Position::ChangeType> Position::changeTypeMap = {
        {"B", Position::ChangeType::Buy},
        {"S", Position::ChangeType::Sell},
        {"D", Position::ChangeType::Dividend}
};


