#pragma once
#include <vector>
#include "PriceSource.h"
class CompositePriceSource : public IPriceSource
{
private:
	std::shared_ptr<IPriceSource> baseSource;
	std::shared_ptr<IPriceSource> multiplierSource;
	Price scalePrice(Price& price, double multiplier);
public:
	CompositePriceSource(const std::shared_ptr<IPriceSource>& baseSource, const std::shared_ptr<IPriceSource>& multiplierSource);
	virtual std::future<Price> GetPriceAsync(const boost::gregorian::date& date) override;
	virtual std::future<std::vector<Price>> GetPricesAsync(const boost::gregorian::date& startDate, const boost::gregorian::date& endDate) override;
};

