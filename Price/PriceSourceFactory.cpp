#include "PriceSourceFactory.h"

std::shared_ptr<IPriceSource> PriceSourceFactory::Create(const std::string& priceSourceName, const std::string& ticker)
{
    if (priceSourceName == "Yahoo")
    {
        auto webRequest = std::make_shared<WebRequest>("G:/Program Files/Git/mingw64/etc/ssl/certs/ca-bundle.crt", true);
        return std::make_shared<YahooPriceSource>(ticker, webRequest);
    }
    std::ostringstream error;
    error << "Could not create price source. " << priceSourceName << "is not a recognised source.";
    throw new std::exception(error.str().c_str());
}