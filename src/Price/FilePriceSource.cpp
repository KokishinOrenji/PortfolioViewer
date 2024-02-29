#include <fstream>
#include "FilePriceSource.h"
#include "FilePriceRepository.h"

FilePriceSource::FilePriceSource(
        const std::string& ticker,
        const std::string& filePath)
        : ticker(ticker),
          filePath(filePath)
          {}

std::future<Price> FilePriceSource::GetPriceAsync(const boost::gregorian::date& date) {
    return std::async(std::launch::async, [this, date]() -> Price {
        auto priceRepo = FilePriceRepository::GetInstance(filePath);
        auto prices = priceRepo->GetPrices(ticker);

        auto candidatePrice = prices.end();
        // Assume it's sorted in the file
        for (auto i = prices.begin(); i < prices.end(); ++i) {
            if ((*i).date > date) {
                break;
            }
            candidatePrice = i;
        }
        if (candidatePrice != prices.end())
        {
            return *candidatePrice;
        }
        std::cout << "Could not find price for "
            << ticker
            << " from file for date "
            << boost::gregorian::to_iso_extended_string(date)
            << std::endl;
        return Price::PriceNotFound;
    });
}

std::future<std::vector<Price>> FilePriceSource::GetPricesAsync(const boost::gregorian::date& startDate, const boost::gregorian::date& endDate)
{
    return std::async(std::launch::async, [this, startDate, endDate]() -> std::vector<Price> {
        auto priceRepo = FilePriceRepository::GetInstance(filePath);
        auto prices = priceRepo->GetPrices(ticker);

        std::vector<Price> filteredPrices;
        // Assume it's sorted in the file
        for (const Price & price : prices) {
            if (price.date >= startDate && price.date <= endDate)
            {
                filteredPrices.push_back(price);
            }
        }
        return filteredPrices;
    });
}
