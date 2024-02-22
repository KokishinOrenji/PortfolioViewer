#include "PriceSourceFactory.h"
#include "YahooPriceSource.h"
#include "FilePriceSource.h"

std::shared_ptr<IPriceSource> PriceSourceFactory::Create(const std::string& priceSourceName, const std::string& ticker)
{
    if (priceSourceName == "Yahoo")
    {
        auto httpClient = std::make_shared<HttpClient>("G:\\Program Files\\Git\\mingw64\\etc\\ssl\\certs\\ca-bundle.crt");
        return std::make_shared<YahooPriceSource>(ticker, httpClient);
    }
    if (priceSourceName == "FILE")
    {
        return std::make_shared<FilePriceSource>(ticker, "D:\\Scratch\\Positions\\prices.csv");
    }
    std::ostringstream error;
    error << "Could not create price source. " << priceSourceName << "is not a recognised source.";
    throw new std::exception(error.str().c_str());
}