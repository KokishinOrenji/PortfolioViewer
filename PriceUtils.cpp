#include "PriceUtils.h"
#include <iostream>
#include <boost/lexical_cast.hpp>

bool canConvertToDouble(const std::string& str) {
    try {
        double value = boost::lexical_cast<double>(str);
        return true;
    }
    catch (const boost::bad_lexical_cast&) {
        return false;
    }
}

double tryConvertToDouble(const std::string& str) {
    try {
        double value = boost::lexical_cast<double>(str);
        return value;
    }
    catch (const boost::bad_lexical_cast&) {
        std::stringstream error;
        error << "Cannot convert '" << str << "' to double. Returning 0.0.";
        std::cerr << error.str();
        return 0.0;
    }
}

