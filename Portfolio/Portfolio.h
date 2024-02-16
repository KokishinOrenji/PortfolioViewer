#ifndef TEST_PORTFOLIO_H
#define TEST_PORTFOLIO_H

#include <vector>
#include "Position.h"

class Portfolio {
public:
    explicit Portfolio(const std::vector<std::shared_ptr<Position>> &positions);
    static const std::vector<std::string> inputColumns;
    static const std::vector<std::string> generatedColumns;
    std::vector<std::shared_ptr<Position>> positions;
    std::string GetCsvFormat(const std::shared_ptr<boost::gregorian::date>& date);
};

class PortfolioFactory {
public:
    static std::shared_ptr<Portfolio> createFromCsv(const std::string & filePath);
    static std::shared_ptr<Portfolio> createFromCsvFileContents(const std::vector<std::string> & contents, bool hasHeaders = true);
};

#endif //TEST_PORTFOLIO_H
