#include "MovingAverageCrossoverStrategy.hpp"
#include <numeric>
#include <iostream>
#include "DataLoader.hpp"
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
    // Use DataLoader to load the data
    DataLoader dataLoader(dataFilePath, "");
    dataLoader.loadData();

    // Get all the close prices
    const auto& allClosePrices = dataLoader.getNumericData().at("close");

    // Ensure we have enough data for the moving averages
    if (allClosePrices.size() < longWindow) {
        std::cerr << "Not enough data to calculate moving averages." << std::endl;
        return "HOLD";
    }

    // Fill the shortPrices and longPrices deques with the most recent data
    for (size_t i = std::max(allClosePrices.size() - longWindow, size_t(0)); i < allClosePrices.size(); ++i) {
        double price = allClosePrices[i];
        shortPrices.push_back(price);
        longPrices.push_back(price);

        if (shortPrices.size() > shortWindow) shortPrices.pop_front();
        if (longPrices.size() > longWindow) longPrices.pop_front();
    }

    // Calculate the short-term and long-term moving averages
    double shortMA = std::accumulate(shortPrices.begin(), shortPrices.end(), 0.0) / shortWindow;
    double longMA = std::accumulate(longPrices.begin(), longPrices.end(), 0.0) / longWindow;

    std::cout << "Short MA: " << shortMA << ", Long MA: " << longMA << std::endl;

    // Make a decision based on the moving averages
    if (shortMA > longMA) {
        return "BUY";  // Predict the stock will move up
    } else if (shortMA < longMA) {
        return "SELL";  // Predict the stock will move down
    }

    return "HOLD";  // No strong prediction
}