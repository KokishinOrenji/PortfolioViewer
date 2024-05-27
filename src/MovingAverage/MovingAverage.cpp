#include <xtensor/xarray.hpp>
#include <xtensor/xview.hpp>
#include <xtensor/xmath.hpp>
#include <numeric>
#include "MovingAverage.h"

xt::xarray<double> MovingAverageCalculator::CalculateSMA(const std::vector<Price>& prices, int period) {
    xt::xarray<double> price_array = xt::zeros<double>({ prices.size() });
    std::transform(prices.begin(), prices.end(), price_array.begin(), [](const Price& p) { return p.close; });

    xt::xarray<double> sma = xt::zeros<double>({ prices.size() - period + 1 });
    for (size_t i = 0; i < sma.size(); ++i) {
        sma[i] = xt::mean(xt::view(price_array, xt::range(i, i + period)))();
    }
    return sma;
}

xt::xarray<double> MovingAverageCalculator::CalculateEMA(const std::vector<Price>& prices, int period) {
    xt::xarray<double> price_array = xt::zeros<double>({ prices.size() });
    std::transform(prices.begin(), prices.end(), price_array.begin(), [](const Price& p) { return p.close; });

    xt::xarray<double> ema = xt::empty<double>({ prices.size() });
    double alpha = 2.0 / (period + 1);
    ema[0] = price_array[0]; // start from the first price
    for (size_t i = 1; i < price_array.size(); ++i) {
        ema[i] = price_array[i] * alpha + ema[i - 1] * (1 - alpha);
    }
    return ema;
}
