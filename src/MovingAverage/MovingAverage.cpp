#include <xtensor/xarray.hpp>
#include <xtensor/xview.hpp>
#include <xtensor/xmath.hpp>
#include <numeric>
#include "MovingAverage.h"

xt::xarray<double> StatisticsCalculator::calculateSMA(const xt::xarray<double>& prices, int period) {
    xt::xarray<double> sma = xt::zeros<double>({ prices.size() - period + 1 });
    for (size_t i = 0; i < sma.size(); ++i) {
        sma[i] = xt::mean(xt::view(prices, xt::range(i, i + period)))();
    }
    return sma;
}

xt::xarray<double> StatisticsCalculator::calculateEMA(const xt::xarray<double>& prices, int period) {
    xt::xarray<double> ema = xt::empty<double>({ prices.size() });
    double alpha = 2.0 / (period + 1);
    ema[0] = prices[0]; // start from the first price
    for (size_t i = 1; i < prices.size(); ++i) {
        ema[i] = prices[i] * alpha + ema[i - 1] * (1 - alpha);
    }
    return ema;
}

xt::xarray<double> StatisticsCalculator::calculateRsi(const xt::xarray<double>& prices, int period) {
    xt::xarray<double> deltas = xt::diff(prices, 1);
    xt::xarray<double> gains = xt::clip(deltas, 0.0, xt::amax(deltas));
    xt::xarray<double> losses = xt::clip(deltas, xt::amin(deltas), 0.0);

    xt::xarray<double> avg_gain = xt::zeros<double>({ prices.size() });
    xt::xarray<double> avg_loss = xt::zeros<double>({ prices.size() });

    for (int i = period; i < prices.size(); i++) {
        avg_gain[i] = xt::mean(xt::view(gains, xt::range(i - period, i)))(0);
        avg_loss[i] = -xt::mean(xt::view(losses, xt::range(i - period, i)))(0);
    }

    xt::xarray<double> rs = avg_gain / avg_loss;
    xt::xarray<double> rsi = 100 - (100 / (1 + rs));
    return rsi;
}

xt::xarray<double> StatisticsCalculator::calculateBollingerBands(const xt::xarray<double>& prices, int period, double num_std_dev) {
    xt::xarray<double> middle_band = calculateSMA(prices, period);
    xt::xarray<double> std_dev = xt::sqrt(calculateSMA(xt::pow(prices - middle_band, 2), period));

    xt::xarray<double> upper_band = middle_band + num_std_dev * std_dev;
    xt::xarray<double> lower_band = middle_band - num_std_dev * std_dev;

    return xt::stack(xt::xtuple(middle_band, upper_band, lower_band), 0);
}

xt::xarray<double> StatisticsCalculator::stochasticOscillator(const xt::xarray<double>& highs, const xt::xarray<double>& lows, const xt::xarray<double>& closes, int period) {
    xt::xarray<double> k_values = xt::zeros<double>(closes.shape());

    for (size_t i = period - 1; i < closes.size(); ++i) {
        double low_min = xt::amin(xt::view(lows, xt::range(i - period + 1, i + 1)))(0);
        double high_max = xt::amax(xt::view(highs, xt::range(i - period + 1, i + 1)))(0);
        k_values[i] = ((closes[i] - low_min) / (high_max - low_min)) * 100;
    }

    return k_values;
}

template<typename Func>
xt::xarray<double> vectorPriceToXArray(const std::vector<Price>& prices, Func extractor = [](const Price& p) { return p.close; }) {
    xt::xarray<double> closeValues = xt::zeros<double>({ prices.size() });
    for (size_t i = 0; i < prices.size(); ++i) {
        closeValues(i) = extractor(prices[i]);
    }
    return closeValues;
}

xt::xarray<double> StatisticsCalculator::calculateSMA(const std::vector<Price>& prices, int period) {
    return calculateSMA(vectorPriceToXArray(prices, [](const Price& p) { return p.close; }), period);
}

xt::xarray<double> StatisticsCalculator::calculateEMA(const std::vector<Price>& prices, int period) {
    return calculateEMA(vectorPriceToXArray(prices, [](const Price& p) { return p.close; }), period);
}

xt::xarray<double> StatisticsCalculator::calculateRsi(const std::vector<Price>& prices, int period) {
    return calculateBollingerBands(vectorPriceToXArray(prices, [](const Price& p) { return p.close; }), period);
}

xt::xarray<double> StatisticsCalculator::calculateBollingerBands(const std::vector<Price>& prices, int period, double num_std_dev) {
    return calculateBollingerBands(vectorPriceToXArray(prices, [](const Price& p) { return p.close; }), period, num_std_dev);
}

xt::xarray<double> StatisticsCalculator::stochasticOscillator(const std::vector<Price>& prices, int period) {
    return stochasticOscillator(
        vectorPriceToXArray(prices, [](const Price& p) { return p.high; }),
        vectorPriceToXArray(prices, [](const Price& p) { return p.low; }),
        vectorPriceToXArray(prices, [](const Price& p) { return p.close; }),
        period);
}
