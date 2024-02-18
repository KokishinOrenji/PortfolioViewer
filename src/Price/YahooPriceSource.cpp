#include <boost/date_time/posix_time/ptime.hpp>
#include "YahooPriceSource.h"
#include "WebPriceSource.h"

YahooPriceSource::YahooPriceSource(
        const std::string& ticker,
        const std::shared_ptr<IHttpClient>& webRequest)
        : ticker(ticker),
          WebPriceSource(webRequest),
          url("https://query1.finance.yahoo.com/v7/finance/download/$ticker?period1=$start&period2=$end&interval=1d&events=history&includeAdjustedClose=true")
{}

std::future<std::shared_ptr<Price>> YahooPriceSource::GetPriceAsync(const boost::gregorian::date& date) {
    return std::async(std::launch::async, [this, date]() -> std::shared_ptr<Price> {
        std::cout << "Starting " << ticker << std::endl;
        auto urlWithSubs = url;
        auto nextDay = date + boost::gregorian::days(1);
        auto startString = ConvertToTTime(date);
        auto endString = ConvertToTTime(nextDay);
        boost::algorithm::replace_all(urlWithSubs, "$ticker", ticker);
        boost::algorithm::replace_all(urlWithSubs, "$start", startString);
        boost::algorithm::replace_all(urlWithSubs, "$end", endString);

        std::cout << url << std::endl;
        std::cout << urlWithSubs << std::endl;

        // Assuming GetAsync returns a future<string>
        auto futureFromWeb = GetAsync(urlWithSubs);

        // Wait for the async operation to finish and get the result
        std::string fromWeb = futureFromWeb.get();

        std::vector<std::string> tokens;
        std::string token;
        std::istringstream stream(fromWeb);
        while (std::getline(stream, token)) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            throw std::runtime_error("Could not retrieve price for: " + ticker + ":" + fromWeb);
        }

        std::cout << "Ending " << ticker << std::endl;
        return std::make_shared<Price>(tokens[1]);
    });
}


std::string YahooPriceSource::ConvertToTTime(const boost::gregorian::date& date)
{
    boost::posix_time::ptime pt(date);

    // Convert to time_t
    boost::posix_time::ptime epoch(boost::gregorian::date(1970, 1, 1));
    boost::posix_time::time_duration::sec_type seconds = (pt - epoch).total_seconds();
    return std::to_string(seconds);
}

