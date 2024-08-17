#include "MovingAverageCrossoverStrategy.hpp"
#include <numeric>
#include <iostream>

void MovingAverageCrossoverStrategy::initialize(const std::map<std::string, double>& params) {
    shortWindow = params.at("shortWindow");
    longWindow = params.at("longWindow");
}

void MovingAverageCrossoverStrategy::execute(Portfolio& portfolio, const std::map<std::string, double>& data, bool hasPosition) {
    double priceClose = data.at("Close");

    shortPrices.push_back(priceClose);
    longPrices.push_back(priceClose);

    if (shortPrices.size() > shortWindow) shortPrices.pop_front();
    if (longPrices.size() > longWindow) longPrices.pop_front();

    if (shortPrices.size() == shortWindow && longPrices.size() == longWindow) {
        double shortMA = std::accumulate(shortPrices.begin(), shortPrices.end(), 0.0) / shortWindow;
        double longMA = std::accumulate(longPrices.begin(), longPrices.end(), 0.0) / longWindow;

        std::cout << "Short MA: " << shortMA << ", Long MA: " << longMA << std::endl;

        if (shortMA > longMA && !hasPosition) {
            std::cout << "Buying at " << priceClose << std::endl;
            portfolio.addTrade(Trade("AAPL", priceClose, 100, "2024-01-01"));
            hasPosition = true;
        } else if (shortMA <= longMA && hasPosition) {
            std::cout << "Selling at " << priceClose << std::endl;
            portfolio.closeTrade("AAPL", priceClose, 100, "2024-01-15");
            hasPosition = false;
        }
    }
}


