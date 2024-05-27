#include "TradingStrategy.h"

TradingStrategy::Action TradingStrategy::DetermineAction(const xt::xarray<double>& short_ma, const xt::xarray<double>& long_ma) {
    if (short_ma(short_ma.size() - 1) > long_ma(long_ma.size() - 1) &&
        short_ma(short_ma.size() - 2) <= long_ma(long_ma.size() - 2)) {
        return Action::Buy; // Short MA crosses above Long MA
    }
    else if (short_ma(short_ma.size() - 1) < long_ma(long_ma.size() - 1) &&
        short_ma(short_ma.size() - 2) >= long_ma(long_ma.size() - 2)) {
        return Action::Sell; // Short MA crosses below Long MA
    }
    return Action::Hold;
}
