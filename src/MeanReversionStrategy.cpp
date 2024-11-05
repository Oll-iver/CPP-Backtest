#include "MeanReversionStrategy.hpp"
#include <numeric>
#include <cmath>
#include <iostream>
#include "DataLoader.hpp"
#include "Portfolio.hpp"



//Constructor with default values
MeanReversionStrategy::MeanReversionStrategy() 
    : windowSize(14), threshold(2.0), hasPosition(false) {}

void MeanReversionStrategy::initialize(const std::map<std::string, double>& params) {
    if (params.find("windowSize") != params.end()) {
        windowSize = static_cast<int>(params.at("windowSize"));
    }
    if (params.find("threshold") != params.end()) {
        threshold = params.at("threshold");
    }
}

bool MeanReversionStrategy::isPositionHeld() const {
    return hasPosition;
}

void MeanReversionStrategy::execute(Portfolio& portfolio, const std::map<std::string, double>& data) {
    if (data.find("close") == data.end()) return;


    double price = data.at("close");
    prices.push_back(price);
    if (prices.size() > windowSize) prices.pop_front();

    if (prices.size() == windowSize) {
        //Calculate mean and standard deviation
        double mean = std::accumulate(prices.begin(), prices.end(), 0.0) / windowSize;
        double variance = std::accumulate(prices.begin(), prices.end(), 0.0,
            [&](double sum, double p) { return sum + (p - mean) * (p - mean); }) / windowSize;
        double stddev = std::sqrt(variance);

        //Trading logic
        if (hasPosition && price > mean + threshold * stddev) {
            portfolio.closeTrade("AAPL", price, 100, "2024-01-15"); // Exit trade
            hasPosition = false;
        } else if (!hasPosition && price < mean - threshold * stddev) {
            portfolio.addTrade(Trade("AAPL", price, 100, "2024-01-01")); // Enter trade
            hasPosition = true;
        }
    }
}

std::string MeanReversionStrategy::makeDecision(const std::string& dataFilePath) {
    DataLoader dataLoader(dataFilePath, "");
    dataLoader.loadData();
    const auto& numericData = dataLoader.getNumericData();

    if (numericData.find("close") == numericData.end()) return "HOLD";

    const auto& allClosePrices = numericData.at("close");

    if (allClosePrices.empty()) return "HOLD";

    for (const auto& price : allClosePrices) {
        prices.push_back(price);
        if (prices.size() > windowSize) prices.pop_front();
    }

    if (prices.size() == windowSize) {
        double mean = std::accumulate(prices.begin(), prices.end(), 0.0) / prices.size();
        double variance = std::accumulate(prices.begin(), prices.end(), 0.0,
            [&](double sum, double p) { return sum + (p - mean) * (p - mean); }) / prices.size();
        double stddev = std::sqrt(variance);

        //Decision based on deviation
        if (prices.back() <= mean - threshold * stddev) {
            return "BUY";
        } else if (prices.back() >= mean + threshold * stddev) {
            return "SELL";
        }
    }
    return "HOLD";
}
