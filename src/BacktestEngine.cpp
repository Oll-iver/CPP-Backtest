#include "BacktestEngine.hpp"
#include <iostream>
#include <map>

BacktestEngine::BacktestEngine(const std::string& dataFilePath, const std::string& portfolioFilePath, SimpleStrategy* strategy, double initialCash)
    : dataLoader(dataFilePath, portfolioFilePath), strategy(strategy), portfolio(initialCash) {}

void BacktestEngine::run() {
    // Load data and portfolio
    dataLoader.loadData();
    dataLoader.loadPortfolio(portfolio);

    const auto& numericData = dataLoader.getNumericData();
    const auto& stringData = dataLoader.getStringData();

    const auto& dates = stringData.at("date");
    const auto& opens = numericData.at("open");
    const auto& closes = numericData.at("close");

    // Ensure that the sizes of vectors match
    if (dates.size() != opens.size() || dates.size() != closes.size()) {
        std::cerr << "Data inconsistency: Mismatched vector sizes." << std::endl;
        return;
    }

    for (size_t i = 0; i < dates.size(); ++i) {
        std::string date = dates[i];
        double openPrice = opens[i];
        double closePrice = closes[i];

        // Execute the strategy on the portfolio using the current day's data
        std::map<std::string, double> dailyData = {{"open", openPrice}, {"close", closePrice}};
        strategy->execute(portfolio, dailyData);

        // Logging the processing step
        std::cout << "Processing on " << date << ": Open = " << openPrice << ", Close = " << closePrice << std::endl;
    }
}
