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
    virtual std::future<std::shared_ptr<Price>> GetPriceAsync(const boost::gregorian::date& date) = 0;
	virtual ~IPriceSource() {}
};

