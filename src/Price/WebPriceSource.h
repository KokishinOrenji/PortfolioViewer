#ifndef PORTFOLIOVIEWER_WEBPRICESOURCE_H
#define PORTFOLIOVIEWER_WEBPRICESOURCE_H

#include "PriceSource.h"

class WebPriceSource : public IPriceSource {
private:
    std::shared_ptr<IHttpClient> webRequest;

public:
    WebPriceSource(const std::shared_ptr<IHttpClient>& webRequest);

protected:
    std::future<std::string> GetAsync(const std::string & url);

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
};

#endif //PORTFOLIOVIEWER_WEBPRICESOURCE_H
