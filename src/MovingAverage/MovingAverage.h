#include <xtensor/xarray.hpp>
#include "../Price/Price.h"
//#include <xtensor/xview.hpp>
//#include <xtensor/xmath.hpp>
//#include <numeric>

class StatisticsCalculator {
public:
    static xt::xarray<double> calculateSMA(const xt::xarray<double>& prices, int period);
    static xt::xarray<double> calculateEMA(const xt::xarray<double>& prices, int period);
    static xt::xarray<double> calculateRsi(const xt::xarray<double>& prices, int period = 14);
    static xt::xarray<double> calculateBollingerBands(const xt::xarray<double>& prices, int period = 20, double num_std_dev = 2);
    static xt::xarray<double> stochasticOscillator(const xt::xarray<double>& highs, const xt::xarray<double>& lows, const xt::xarray<double>& closes, int period = 14);

    static xt::xarray<double> calculateSMA(const std::vector<Price>& prices, int period);
    static xt::xarray<double> calculateEMA(const std::vector<Price>& prices, int period);
    static xt::xarray<double> calculateRsi(const std::vector<Price>& prices, int period = 14);
    static xt::xarray<double> calculateBollingerBands(const std::vector<Price>& prices, int period = 20, double num_std_dev = 2);
    static xt::xarray<double> stochasticOscillator(const std::vector<Price>& prices, int period = 14);
};
