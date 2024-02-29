#ifndef PORTFOLIO_VIEWER_FILEPRICEREPOSITORY_H
#define PORTFOLIO_VIEWER_FILEPRICEREPOSITORY_H

#include <fstream>
#include <unordered_map>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <mutex>
#include "Price.h"

class FilePriceRepository {
private:
    std::unordered_map<std::string, std::vector<Price>> priceMap;
    std::string filePath;
    static std::mutex instanceMutex;

    void LoadData();
public:
    FilePriceRepository(const std::string& filePath) : filePath(filePath) {}
    static std::shared_ptr<FilePriceRepository> GetInstance(const std::string& filePath);
    const std::vector<Price>& GetPrices(const std::string& ticker) {
        return priceMap[ticker];
    }
    // Delete copy constructor and assignment operator
    FilePriceRepository(const FilePriceRepository&) = delete;
    FilePriceRepository& operator=(const FilePriceRepository&) = delete;
};

#endif //PORTFOLIO_VIEWER_FILEPRICEREPOSITORY_H
