#ifndef TEST_PRICESOURCEFACTORY_H
#define TEST_PRICESOURCEFACTORY_H


#include <memory>
#include "PriceSource.h"

class PriceSourceFactory {
public:
    static std::shared_ptr<IPriceSource> Create(const std::string& priceSourceName);
};


#endif //TEST_PRICESOURCEFACTORY_H
