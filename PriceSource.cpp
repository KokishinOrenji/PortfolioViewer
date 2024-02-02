#include "PriceSource.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp> // For JSON parsing

WebPriceSource::WebPriceSource(const std::shared_ptr<IWebRequest>& webRequest)
        :webRequest(webRequest)
{}

std::string WebPriceSource::Get(const std::string & url)
{
    return webRequest->Get(url);
}

YahooPriceSource::YahooPriceSource(
        const std::string& ticker,
        const std::shared_ptr<IWebRequest>& webRequest)
: ticker(ticker),
WebPriceSource(webRequest),
url("https://query1.finance.yahoo.com/v7/finance/download/$ticker?period1=$start&period2=$end&interval=1d&events=history&includeAdjustedClose=true")
{}

std::shared_ptr<Price> YahooPriceSource::GetPrice(const std::shared_ptr<boost::gregorian::date>& date)
{
    auto urlWithSubs = url;
    auto nextDay = std::make_shared<boost::gregorian::date>(*date + boost::gregorian::days(1));
    auto startString =  ConvertToTTime(date);
    auto endString =  ConvertToTTime(nextDay);
    boost::algorithm::replace_all(urlWithSubs, "$ticker", ticker);
    boost::algorithm::replace_all(urlWithSubs, "$start", startString);
    boost::algorithm::replace_all(urlWithSubs, "$end", endString);
    std::cout << url << std::endl;
    std::cout << urlWithSubs << std::endl;
    auto fromWeb = Get(urlWithSubs);
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(fromWeb);
    while (std::getline(stream, token))
    {
        tokens.push_back(token);
    }
    if (tokens.size() < 2)
    {
        throw new std::exception(std::string("Could not retrieve price for: " + ticker + ":" + fromWeb).c_str());
    }

    //std::string date, double open, double high, double low, double close, double adjClose, long volume
    return std::make_shared<Price>(tokens[1]);
}

std::string YahooPriceSource::ConvertToTTime(const std::shared_ptr<boost::gregorian::date>& date)
{
    boost::posix_time::ptime pt(*date);

    // Convert to time_t
    boost::posix_time::ptime epoch(boost::gregorian::date(1970, 1, 1));
    boost::posix_time::time_duration::sec_type seconds = (pt - epoch).total_seconds();
    return std::to_string(seconds);
}
/*

CoinGeckoSource::CoinGeckoSource(
        const std::string& ticker,
        const std::shared_ptr<IWebRequest>& webRequest)
        : ticker(ticker),
          WebPriceSource(webRequest),
          url("https://min-api.cryptocompare.com/data/pricemultifull?fsyms=$symbols&tsyms=USD,GBP")
{}

std::string apiUrl = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd"; // Example API URL


std::shared_ptr<Price> CoinGeckoSource::GetPrice(const std::shared_ptr<boost::gregorian::date>& date)
{
    auto urlWithSubs = url;
    auto nextDay = std::make_shared<boost::gregorian::date>(*date + boost::gregorian::days(1));
    auto startString =  ConvertToTTime(date);
    auto endString =  ConvertToTTime(nextDay);
    boost::algorithm::replace_all(urlWithSubs, "$ticker", ticker);
    boost::algorithm::replace_all(urlWithSubs, "$start", startString);
    boost::algorithm::replace_all(urlWithSubs, "$end", endString);
    std::cout << url << std::endl;
    std::cout << urlWithSubs << std::endl;
    auto fromWeb = Get(urlWithSubs);
    return 0;
}
*/
