#pragma once

#include <string>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <future>
#include "HttpClient.h"
#include "Price.h"

class IPriceSource
{
public:
    virtual std::future<Price> GetPriceAsync(const boost::gregorian::date& date) = 0;
    virtual std::future<std::vector<Price>> GetPricesAsync(const boost::gregorian::date& startDate, const boost::gregorian::date& endDate) = 0;
	virtual ~IPriceSource() {}
};

