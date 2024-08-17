#include "BacktestEngine.hpp"
#include <iostream>

BacktestEngine::BacktestEngine(const std::string& dataFilePath, Strategy* strategy, double initialCash)
    : dataLoader(dataFilePath), strategy(strategy), portfolio(initialCash) {}

void BacktestEngine::run() {
    dataLoader.loadData();

    const auto& numericData = dataLoader.getNumericData();
    const auto& stringData = dataLoader.getStringData();

    const auto& dates = stringData.at("Date");
    const auto& symbols = stringData.at("Symbol");
    const auto& opens = numericData.at("Open");
    const auto& closes = numericData.at("Close");

    for (size_t i = 0; i < dates.size(); ++i) {
        std::string date = dates[i];
        std::string symbol = symbols[i];
        double openPrice = opens[i];
        double closePrice = closes[i];

        // Execute the strategy on the portfolio using the current day's data
        std::map<std::string, double> dailyData = {{"Open", openPrice}, {"Close", closePrice}, {"Date", std::stod(date)}};
        strategy->execute(portfolio, dailyData, false);

        std::cout << "Processing " << symbol << " on " << date << ": "
                  << "Open = " << openPrice << ", Close = " << closePrice << std::endl;
    }
}
