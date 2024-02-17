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
    std::future<std::shared_ptr<Price>> GetPriceAsync(const boost::gregorian::date& date) override;
};

#endif //PORTFOLIOVIEWER_FILEPRICESOURCE_H
