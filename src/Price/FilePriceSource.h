#ifndef PORTFOLIOVIEWER_FILEPRICESOURCE_H
#define PORTFOLIOVIEWER_FILEPRICESOURCE_H

#include <string>
#include "PriceSource.h"

class FilePriceSource : public IPriceSource {
private:
    const std::string ticker;
    const std::string filePath;
public:
    FilePriceSource(const std::string &ticker, const std::string &filePath);
    std::future<Price> GetPriceAsync(const boost::gregorian::date& date) override;
    std::future<std::vector<Price>> GetPricesAsync(const boost::gregorian::date& startDate, const boost::gregorian::date& endDate) override;
};

#endif //PORTFOLIOVIEWER_FILEPRICESOURCE_H
