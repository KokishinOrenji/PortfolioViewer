#include "Position.h"

Position::Position(
        const std::string &ticker,
        const std::string &type,
        const std::string &liquidityType,
        const std::string &priceSourceName,
        const std::shared_ptr<IPriceSource> &priceSource,
        double quantity)
        : priceSource(priceSource),
          quantity(quantity), ticker(ticker),
          type(type),
          liquidityType(liquidityType),
          priceSourceName(priceSourceName) {}

std::future<double> Position::GetPriceAsync(const std::shared_ptr<boost::gregorian::date>& date)
{
    return std::async(std::launch::async, [this, date]() -> double {
       auto price = priceSource->GetPriceAsync(date);
        return price.get()->adjClose;
    });
}