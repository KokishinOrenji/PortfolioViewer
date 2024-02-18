#include "WebPriceSource.h"

WebPriceSource::WebPriceSource(const std::shared_ptr<IHttpClient>& webRequest)
        :webRequest(webRequest)
{}

std::future<std::string> WebPriceSource::GetAsync(const std::string & url)
{
    return webRequest->GetAsync(url);
}
