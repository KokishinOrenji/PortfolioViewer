#include <xtensor/xarray.hpp>

class TradingStrategy {
public:
    enum class Action { Buy, Sell, Hold };

    static Action DetermineAction(const xt::xarray<double>& short_ma, const xt::xarray<double>& long_ma);
};
