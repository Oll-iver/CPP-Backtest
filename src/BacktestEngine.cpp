#include "BacktestEngine.hpp"
#include <iostream>
#include <map>

//Initialises the backtest engine
BacktestEngine::BacktestEngine(const std::string& dataFilePath, const std::string& portfolioFilePath, SimpleStrategy* strategy, double initialCash)
    : dataLoader(dataFilePath, portfolioFilePath), strategy(strategy), portfolio(initialCash) {}


void BacktestEngine::run() {
    // Load data and portfolio
    dataLoader.loadData();
    dataLoader.loadPortfolio(portfolio);

    //Get numeric and string data
    const auto& numericData = dataLoader.getNumericData();
    const auto& stringData = dataLoader.getStringData();

    //Extract specific data vectors for dates, open prices, closing prices
    const auto& dates = stringData.at("date");
    const auto& opens = numericData.at("open");
    const auto& closes = numericData.at("close");

    // Check for data consistency (ensure vector sizes match)
    if (dates.size() != opens.size() || dates.size() != closes.size()) {
        std::cerr << "Data inconsistency: Mismatched vector sizes." << std::endl;
        return;
    }

    //Iterate through each day in the data set
    for (size_t i = 0; i < dates.size(); ++i) {
        std::string date = dates[i];
        double openPrice = opens[i];
        double closePrice = closes[i];

        // Execute the strategy on the portfolio using the current day's data (retrieved above)
        std::map<std::string, double> dailyData = {{"open", openPrice}, {"close", closePrice}};
        strategy->execute(portfolio, dailyData);
    }
}
