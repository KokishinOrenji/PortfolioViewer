#ifndef PORTFOLIOVIEWER_PORTFOLIO_H
#define PORTFOLIOVIEWER_PORTFOLIO_H

#include <vector>
#include "Position.h"

class Portfolio {
public:
    explicit Portfolio(const std::vector<std::shared_ptr<Position>> &positions);
    static const std::vector<std::string> inputColumns;
    static const std::vector<std::string> optionalInputColumns;
    static const std::vector<std::string> generatedColumns;
    std::vector<std::shared_ptr<Position>> positions;
    std::string GetCsvFormat(const boost::gregorian::date& date);
};

class PortfolioFactory {
public:
    static std::shared_ptr<Portfolio> createFromCsv(const std::string & filePath, const boost::gregorian::date & date);
    static std::shared_ptr<Portfolio> createFromCsvFileContents(
            const std::vector<std::string> & contents,
            const boost::gregorian::date & date,
            bool hasHeaders = true);
};

#endif //PORTFOLIOVIEWER_PORTFOLIO_H
