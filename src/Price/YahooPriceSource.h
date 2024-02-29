#ifndef PORTFOLIOVIEWER_YAHOOPRICESOURCE_H
#define PORTFOLIOVIEWER_YAHOOPRICESOURCE_H

#include "PriceSource.h"
#include "WebPriceSource.h"

class YahooPriceSource : public WebPriceSource {
private:
    const std::string ticker;
    const std::string url;
    const bool verbose;

public:
    YahooPriceSource(
            const std::string& ticker,
            const std::shared_ptr<IHttpClient>& webRequest,
            bool verbose = false);

    std::future<Price> GetPriceAsync(const boost::gregorian::date& date) override;
    std::future<std::vector<Price>> GetPricesAsync(const boost::gregorian::date& startDate, const boost::gregorian::date& endDate) override;

private:
    static std::string ConvertToTTime(const boost::gregorian::date& date);
};

#endif //PORTFOLIOVIEWER_YAHOOPRICESOURCE_H
