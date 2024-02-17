#include "PriceSource.h"
#include <nlohmann/json.hpp> // For JSON parsing

WebPriceSource::WebPriceSource(const std::shared_ptr<IWebRequest>& webRequest)
        :webRequest(webRequest)
{}

std::future<std::string> WebPriceSource::GetAsync(const std::string & url)
{
    return webRequest->GetAsync(url);
}
