#ifndef TEST_PRICESOURCEFACTORY_H
#define TEST_PRICESOURCEFACTORY_H


#include <memory>
#include "PriceSource.h"

class PriceSourceFactory {
public:
    static std::shared_ptr<IPriceSource> Create(const std::string& priceSourceName, const std::string& ticker);
};


#endif //TEST_PRICESOURCEFACTORY_H
