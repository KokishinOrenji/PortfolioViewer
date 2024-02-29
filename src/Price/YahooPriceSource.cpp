#include <boost/date_time/posix_time/ptime.hpp>
#include "YahooPriceSource.h"
#include "WebPriceSource.h"

YahooPriceSource::YahooPriceSource(
        const std::string& ticker,
        const std::shared_ptr<IHttpClient>& webRequest,
        bool verbose)
        : ticker(ticker),
          WebPriceSource(webRequest),
          url("https://query1.finance.yahoo.com/v7/finance/download/$ticker?period1=$start&period2=$end&interval=1d&events=history&includeAdjustedClose=true"),
          verbose(verbose)
{}

std::future<Price> YahooPriceSource::GetPriceAsync(const boost::gregorian::date& date) {
    return std::async(std::launch::async, [this, date]() -> Price {
        auto startDay = date + boost::gregorian::days(-7);
        auto prices = GetPricesAsync(startDay, date).get();
        auto closestPrice = std::find_if(
                prices.crbegin(),
                prices.crend(),
                [date](const Price & price) { return price.date <= date; });
        if (closestPrice != prices.crend())
        {
            if (closestPrice->date != date)
            {
                std::stringstream error;
                error << "Could not find a price for "
                    << ticker
                    << " for this date "
                    << boost::gregorian::to_iso_extended_string(date)
                    << " using price from this date instead: "
                    << boost::gregorian::to_iso_extended_string(closestPrice->date)
                    << std::endl;
            }
            return *closestPrice;
        }
        std::cout << "Could not find price for "
                  << ticker
                  << " from Yahoo for date "
                  << boost::gregorian::to_iso_extended_string(date)
                  << std::endl;
        return Price::PriceNotFound;
    });
}

std::future<std::vector<Price>> YahooPriceSource::GetPricesAsync(const boost::gregorian::date& startDate, const boost::gregorian::date& endDate) {
    return std::async(std::launch::async, [this, startDate, endDate]() -> std::vector<Price> {
        if (verbose) {
            std::cout << "Starting " << ticker << std::endl;
        }
        // Construct the URL with start and end dates
        auto urlWithSubs = url;
        auto startString = ConvertToTTime(startDate);
        auto endString = ConvertToTTime(endDate);
        boost::algorithm::replace_all(urlWithSubs, "$ticker", ticker);
        boost::algorithm::replace_all(urlWithSubs, "$start", startString);
        boost::algorithm::replace_all(urlWithSubs, "$end", endString);

        if (verbose) {
            std::cout << url << std::endl;
            std::cout << urlWithSubs << std::endl;
        }

        // Assuming GetAsync returns a future<string>
        auto futureFromWeb = GetAsync(urlWithSubs);

        // Wait for the async operation to finish and get the result
        std::string fromWeb = futureFromWeb.get();

        // Parse the response and populate the vector of prices
        std::vector<Price> prices;
        std::istringstream stream(fromWeb);
        std::string line;
        std::getline(stream, line); // Skip header line
        while (std::getline(stream, line)) {
            if (line.find("null") == std::string::npos) {
                prices.emplace_back(line);
            }
            else {
                std::cout << "Could not parse prices for "
                    << ticker
                    << ". Input: "
                    << line
                    << std::endl;
            }
        }

        if (prices.empty()) {
            std::cout << "No prices retrieved for: " + ticker;
        }

        if (verbose) {
            std::cout << "Ending " << ticker << std::endl;
        }
        return prices;
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

