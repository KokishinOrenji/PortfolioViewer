#include "CompositePriceSource.h"

CompositePriceSource::CompositePriceSource(const std::shared_ptr<IPriceSource>& baseSource, const std::shared_ptr<IPriceSource>& multiplierSource)
	:baseSource(baseSource), multiplierSource(multiplierSource)
{}

std::future<Price> CompositePriceSource::GetPriceAsync(const boost::gregorian::date& date) {
    return std::async(std::launch::async, [this, date]() -> Price {
		auto basePrice = baseSource->GetPriceAsync(date).get();
		auto multiplier = multiplierSource->GetPriceAsync(date).get().adjClose;
		return scalePrice(basePrice, multiplier);
	});
}

std::future<std::vector<Price>> CompositePriceSource::GetPricesAsync(const boost::gregorian::date& startDate, const boost::gregorian::date& endDate) {
	return std::async(std::launch::async, [this, startDate, endDate]() -> std::vector<Price> {
		auto basePrices = baseSource->GetPricesAsync(startDate, endDate).get();
		auto multipliers = multiplierSource->GetPricesAsync(startDate, endDate).get();
		std::vector<Price> scaledPrices;
		for (auto& basePrice : basePrices) {
			auto it = std::find_if(multipliers.begin(), multipliers.end(), [&basePrice](const Price& multiplierPrice) {
				return basePrice.date == multiplierPrice.date;
			});

			if (it != multipliers.end()) {
				scaledPrices.push_back(scalePrice(basePrice, it->adjClose));
			}
		}
		return scaledPrices;
	});
}

Price CompositePriceSource::scalePrice(Price& price, double multiplier) {
	price.adjClose *= multiplier;
	price.close *= multiplier;
	price.low *= multiplier;
	price.high *= multiplier;
	price.open *= multiplier;
	return price;
}