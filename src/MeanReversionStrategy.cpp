#include "MeanReversionStrategy.hpp"
#include <numeric>
#include <cmath>
#include <iostream>
#include "DataLoader.hpp"
#include "Portfolio.hpp"

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
    try {
        if (data.find("close") == data.end()) {
            std::cerr << "Key 'close' not found in data map." << std::endl;
            return; // Handle the error as appropriate
        }
        double price = data.at("close");
        prices.push_back(price);
        if (prices.size() > windowSize) prices.pop_front();

        if (prices.size() == windowSize) {
            double mean = std::accumulate(prices.begin(), prices.end(), 0.0) / windowSize;
            double variance = std::accumulate(prices.begin(), prices.end(), 0.0,
                [&](double sum, double p) { return sum + (p - mean) * (p - mean); }) / windowSize;
            double stddev = std::sqrt(variance);

            if (hasPosition) {
                if (price > mean + threshold * stddev) {
                    portfolio.closeTrade("AAPL", price, 100, "2024-01-15");
                    hasPosition = false;
                    std::cout << "Sold at " << price << std::endl;
                }
            } else {
                if (price < mean - threshold * stddev) {
                    portfolio.addTrade(Trade("AAPL", price, 100, "2024-01-01"));
                    hasPosition = true;
                    std::cout << "Bought at " << price << std::endl;
                }
            }
        }
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range error in execute(): " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception in execute(): " << e.what() << std::endl;
    }
}



std::string MeanReversionStrategy::makeDecision(const std::string& dataFilePath) {
    DataLoader dataLoader(dataFilePath, "");
    dataLoader.loadData();

    // Safeguard access to "open" and "close" keys
    if (dataLoader.getNumericData().find("close") == dataLoader.getNumericData().end()) {
        std::cerr << "Key 'close' not found in numericData map." << std::endl;
        return "HOLD";
    }
    if (dataLoader.getNumericData().find("open") == dataLoader.getNumericData().end()) {
        std::cerr << "Key 'open' not found in numericData map." << std::endl;
        return "HOLD";
    }

    const auto& allClosePrices = dataLoader.getNumericData().at("close");
    const auto& allOpenPrices = dataLoader.getNumericData().at("open");

    size_t numEntries = allOpenPrices.size();

    for (size_t i = 0; i < numEntries; ++i) {
        if (i >= allClosePrices.size()) {
            std::cerr << "Index " << i << " exceeds the size of allClosePrices vector." << std::endl;
            break;  // Handle this case appropriately
        }

        double openPrice = allOpenPrices[i];
        std::cout << "Processing AAPL on " << dataLoader.getStringData().at("date")[i]
                  << ": Open = " << openPrice;

        prices.push_back(openPrice);

        if (i < allClosePrices.size()) {
            double closePrice = allClosePrices[i];
            std::cout << ", Close = " << closePrice << std::endl;
            prices.push_back(closePrice);
        } else {
            std::cout << " (Close price missing, only Open price used)" << std::endl;
        }

        while (prices.size() > 2 * windowSize) {
            prices.pop_front();  
        }

        std::cout << "Prices deque after update:" << std::endl;
        for (size_t j = 0; j < prices.size(); ++j) {
            std::cout << "Price " << j + 1 << ": " << prices[j] << std::endl;
        }
    }

    std::cout << "Final deque size: " << prices.size() << std::endl;
    if (prices.size() == 2 * windowSize) {
        double mean = std::accumulate(prices.begin(), prices.end(), 0.0) / prices.size();
        double variance = std::accumulate(prices.begin(), prices.end(), 0.0,
            [&](double sum, double p) { return sum + (p - mean) * (p - mean); }) / prices.size();
        double stddev = std::sqrt(variance);

        std::cout << "VALUE DUMP HERE:" << std::endl;
        std::cout << "Mean: " << mean << std::endl;
        std::cout << "Threshold: " << threshold << std::endl;
        std::cout << "Standard Deviation: " << stddev << std::endl;
        std::cout << "Price: " << prices.back() << std::endl;

        double lowerBound = mean - threshold * stddev;
        double upperBound = mean + threshold * stddev;
        std::cout << "Lower Bound: " << lowerBound << std::endl;
        std::cout << "Upper Bound: " << upperBound << std::endl;

        if (prices.back() <= lowerBound) {
            return "BUY";
        } else if (prices.back() >= upperBound) {
            return "SELL";
        }
    } else {
        std::cout << "Deque did not reach the required size." << std::endl;
    }

    return "HOLD";
}
