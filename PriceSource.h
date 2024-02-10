#pragma once

#include <string>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <future>
#include "WebRequest.h"
#include "Price.h"

class IPriceSource
{
public:
	virtual std::future<std::shared_ptr<Price>> GetPriceAsync(const std::shared_ptr<boost::gregorian::date>& date) = 0;
	virtual ~IPriceSource() {}
};

class WebPriceSource : public IPriceSource {
private:
    std::shared_ptr<IWebRequest> webRequest;

public:
    WebPriceSource(const std::shared_ptr<IWebRequest>& webRequest);

protected:
    std::future<std::string> GetAsync(const std::string & url);

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
};

class YahooPriceSource : public WebPriceSource {
private:
    std::string ticker;
    const std::string url;

public:
	YahooPriceSource(
            const std::string& ticker,
            const std::shared_ptr<IWebRequest>& webRequest);

    std::future<std::shared_ptr<Price>> GetPriceAsync(const std::shared_ptr<boost::gregorian::date>& date);

private:
    static std::string ConvertToTTime(const std::shared_ptr<boost::gregorian::date>& date);
};
/*

class CoinGeckoSource : public WebPriceSource {
private:
    std::string ticker;
    const std::string url;

public:
    CoinGeckoSource(
            const std::string& ticker,
            const std::shared_ptr<IWebRequest>& webRequest);

    std::shared_ptr<Price> GetPriceAsync(const std::shared_ptr<boost::gregorian::date>& date);

private:
    static std::string ConvertToTTime(const std::shared_ptr<boost::gregorian::date>& date);
};*/
