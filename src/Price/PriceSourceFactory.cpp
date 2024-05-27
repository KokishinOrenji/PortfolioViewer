#include "PriceSourceFactory.h"
#include "YahooPriceSource.h"
#include "FilePriceSource.h"
#include "CompositePriceSource.h"

std::shared_ptr<IPriceSource> PriceSourceFactory::Create(const std::string& priceSourceName, const std::string& ticker, const std::string& currency)
{
    if (priceSourceName == "Yahoo")
    {
        auto httpClient = std::make_shared<HttpClient>("G:\\Program Files\\Git\\mingw64\\etc\\ssl\\certs\\ca-bundle.crt");
        auto priceSource = std::make_shared<YahooPriceSource>(ticker, httpClient);
        if (currency != "GBP")
        {
            auto multiplierSource = std::make_shared<YahooPriceSource>(currency + "GBP=X", httpClient);
            return std::make_shared<CompositePriceSource>(priceSource, multiplierSource);
        }
        return priceSource;
    }
    if (priceSourceName == "FILE")
    {
        return std::make_shared<FilePriceSource>(ticker, "D:\\Scratch\\Positions\\prices.csv");
    }
    std::ostringstream error;
    error << "Could not create price source. " << priceSourceName << "is not a recognised source.";
    throw new std::exception(error.str().c_str());
}