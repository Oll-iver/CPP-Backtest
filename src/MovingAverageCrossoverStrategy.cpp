#include "MovingAverageCrossoverStrategy.hpp"
#include <numeric>
#include <iostream>
#include "DataLoader.hpp"


//Initialise default short and long window, sets position flag to false
MovingAverageCrossoverStrategy::MovingAverageCrossoverStrategy() 
    : shortWindow(5), longWindow(20), hasPosition(false) {}

void MovingAverageCrossoverStrategy::initialize(const std::map<std::string, double>& params) {
    if (params.find("shortWindow") != params.end()) {
        shortWindow = static_cast<int>(params.at("shortWindow"));
    }
    if (params.find("longWindow") != params.end()) {
        longWindow = static_cast<int>(params.at("longWindow"));
    }
}

bool MovingAverageCrossoverStrategy::isPositionHeld() const {
    return hasPosition;
}

void MovingAverageCrossoverStrategy::execute(Portfolio& portfolio, const std::map<std::string, double>& data) {
    // Ensure close price exists
    if (data.find("close") ==data.end()) return;
    
    double price = data.at("close");
    shortPrices.push_back(price);
    longPrices.push_back(price);

    //Maintain deque sizes within specified limits
    if (shortPrices.size() > shortWindow) shortPrices.pop_front();
    if (longPrices.size() > longWindow) longPrices.pop_front();

    //Calculate moving averages and apply crossover strategy if sufficient data exists
    if (shortPrices.size() == shortWindow && longPrices.size() == longWindow) {
        double shortMA = std::accumulate(shortPrices.begin(), shortPrices.end(), 0.0) / shortWindow;
        double longMA = std::accumulate(longPrices.begin(), longPrices.end(), 0.0) / longWindow;

        //Buy signal: short crosses above long
        if (shortMA > longMA) {
            if (!hasPosition) {
                portfolio.addTrade(Trade("AAPL", price, 100, "2024-01-01"));
                hasPosition = true;
            }
        //Buy signal: short crosses below long
        } else if (shortMA < longMA) {
            if (hasPosition) {
                portfolio.closeTrade("AAPL", price, 100, "2024-01-15");
                hasPosition = false;
            }
        }
    }
}

std::string MovingAverageCrossoverStrategy::makeDecision(const std::string& dataFilePath) {
    //load the close prices
    DataLoader dataLoader(dataFilePath, "");
    dataLoader.loadData();

    const auto& numericData = dataLoader.getNumericData();
    if (numericData.find("close") == numericData.end()) return "HOLD";

    const auto& allClosePrices = numericData.at("close");

    // ensure enough data exists
    if (allClosePrices.size() < longWindow) return "HOLD";

    // Fill the shortPrices and longPrices deques
    for (size_t i = std::max(allClosePrices.size() - longWindow, size_t(0)); i < allClosePrices.size(); ++i) {
        double price = allClosePrices[i];
        shortPrices.push_back(price);
        longPrices.push_back(price);

        if (shortPrices.size() > shortWindow) shortPrices.pop_front();
        if (longPrices.size() > longWindow) longPrices.pop_front();
    }

    // Calculate the sma and lma
    double shortMA = std::accumulate(shortPrices.begin(), shortPrices.end(), 0.0) / shortWindow;
    double longMA = std::accumulate(longPrices.begin(), longPrices.end(), 0.0) / longWindow;

    //Return decision
    if (shortMA > longMA) {
        return "BUY";  
    } else if (shortMA < longMA) {
        return "SELL";  
    }

    return "HOLD"; 
}
