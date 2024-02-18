#ifndef PORTFOLIOVIEWER_YAHOOPRICESOURCE_H
#define PORTFOLIOVIEWER_YAHOOPRICESOURCE_H

#include "PriceSource.h"
#include "WebPriceSource.h"

class YahooPriceSource : public WebPriceSource {
private:
    const std::string ticker;
    const std::string url;

public:
    YahooPriceSource(
            const std::string& ticker,
            const std::shared_ptr<IHttpClient>& webRequest);

    std::future<std::shared_ptr<Price>> GetPriceAsync(const boost::gregorian::date& date) override;

private:
    static std::string ConvertToTTime(const boost::gregorian::date& date);
};

#endif //PORTFOLIOVIEWER_YAHOOPRICESOURCE_H
