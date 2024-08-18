#include "MovingAverageCrossoverStrategy.hpp"
#include <numeric>
#include <iostream>
#include "DataLoader.hpp"

//Similar to mean reversion strategyg.cpp but not as bad
//this file requires cleanup high priority.


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
    // Ensure "close" exists
    if (data.find("close") == data.end()) {
        std::cerr << "Key 'close' not found in data map." << std::endl;
        return;
    }
    
    double price = data.at("close");
    shortPrices.push_back(price);
    longPrices.push_back(price);

    if (shortPrices.size() > shortWindow) shortPrices.pop_front();
    if (longPrices.size() > longWindow) longPrices.pop_front();

    if (shortPrices.size() == shortWindow && longPrices.size() == longWindow) {
        double shortMA = std::accumulate(shortPrices.begin(), shortPrices.end(), 0.0) / shortWindow;
        double longMA = std::accumulate(longPrices.begin(), longPrices.end(), 0.0) / longWindow;

        if (shortMA > longMA) {
            if (!hasPosition) {
                portfolio.addTrade(Trade("AAPL", price, 100, "2024-01-01"));
                hasPosition = true;
                std::cout << "Bought at " << price << std::endl;
            }
        } else if (shortMA < longMA) {
            if (hasPosition) {
                portfolio.closeTrade("AAPL", price, 100, "2024-01-15");
                hasPosition = false;
                std::cout << "Sold at " << price << std::endl;
            }
        }
    }
}

std::string MovingAverageCrossoverStrategy::makeDecision(const std::string& dataFilePath) {
    //load the data
    DataLoader dataLoader(dataFilePath, "");
    dataLoader.loadData();

    // Check if close exists
    const auto& numericData = dataLoader.getNumericData();
    if (numericData.find("close") == numericData.end()) {
        std::cerr << "Key 'close' not found in numericData map." << std::endl;
        return "HOLD";
    }

    const auto& allClosePrices = numericData.at("close");

    // ensure enough data is present
    if (allClosePrices.size() < longWindow) {
        std::cerr << "Not enough data to calculate moving averages." << std::endl;
        return "HOLD";
    }

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

    std::cout << "Short MA: " << shortMA << ", Long MA: " << longMA << std::endl;

    if (shortMA > longMA) {
        return "BUY";  
    } else if (shortMA < longMA) {
        return "SELL";  
    }

    return "HOLD"; 
}
