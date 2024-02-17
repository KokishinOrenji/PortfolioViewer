#include <fstream>
#include "FilePriceSource.h"
#include "FilePriceRepository.h"

FilePriceSource::FilePriceSource(
        const std::string& ticker,
        const std::string& filePath)
        : ticker(ticker),
          filePath(filePath)
          {}

std::future<std::shared_ptr<Price>> FilePriceSource::GetPriceAsync(const boost::gregorian::date& date) {
    return std::async(std::launch::async, [this, date]() -> std::shared_ptr<Price> {
        auto priceRepo = FilePriceRepository::GetInstance(filePath);
        auto prices = priceRepo->GetPrices(ticker);

        std::shared_ptr<Price> candidatePrice;
        // Assume it's sorted in the file
        for (auto i = prices.begin(); i < prices.end(); ++i) {
            if ((*i)->date > date) {
                break;
            }
            candidatePrice = *i;
        }
        return candidatePrice;
    });
}