#include <xtensor/xarray.hpp>
#include "../Price/Price.h"
//#include <xtensor/xview.hpp>
//#include <xtensor/xmath.hpp>
//#include <numeric>

class MovingAverageCalculator {
public:
    static xt::xarray<double> CalculateSMA(const std::vector<Price>& prices, int period);
    static xt::xarray<double> CalculateEMA(const std::vector<Price>& prices, int period);
};
