#include "MeanReversionStrategy.hpp"
#include <numeric>
#include <cmath>
#include <iostream>
#include "DataLoader.hpp"
#include "Portfolio.hpp"


//this file is basically unreadable. refactoring this code to wrok with an expanded test_data.csv
//left me with a lot of errors that were easily solve but took a while to figure out
//in fixing the errors i created this mess; that works, but is possibly inefficient 
//and has a lot of unnecessary outputs and debugging
//clean up of this file is a high priority.

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
        std::cout << "Executing MeanReversionStrategy..." << std::endl;

        if (data.find("close") == data.end()) {
            std::cerr << "Key 'close' not found in data map." << std::endl;
            return;
        }

        double price;
        if (data.find("close") != data.end()) {
            price = data.at("close");
            std::cout << "Close price found: " << price << std::endl;
        } else {
            std::cerr << "Error: 'close' key not found in data map." << std::endl;
            return; 
        }
        std::cout << "Processing close price: " << price << std::endl;

        prices.push_back(price);
        if (prices.size() > windowSize) prices.pop_front();

        std::cout << "Current deque size: " << prices.size() << std::endl;

        if (prices.size() == windowSize) {
            double mean = std::accumulate(prices.begin(), prices.end(), 0.0) / windowSize;
            double variance = std::accumulate(prices.begin(), prices.end(), 0.0,
                [&](double sum, double p) { return sum + (p - mean) * (p - mean); }) / windowSize;
            double stddev = std::sqrt(variance);

            std::cout << "Mean: " << mean << ", StdDev: " << stddev << ", Price: " << price << std::endl;

            if (hasPosition) {
                if (price > mean + threshold * stddev) {
                    std::cout << "Attempting to close trade..." << std::endl;
                    portfolio.closeTrade("AAPL", price, 100, "2024-01-15");
                    hasPosition = false;
                    std::cout << "Sold at " << price << std::endl;
                }
            } else {
                if (price < mean - threshold * stddev) {
                    std::cout << "Attempting to add trade..." << std::endl;
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
    try {
        std::cout << "Making decision in MeanReversionStrategy..." << std::endl;

        DataLoader dataLoader(dataFilePath, "");
        dataLoader.loadData();

        auto numericData = dataLoader.getNumericData();

        if (numericData.find("close") == numericData.end()) {
            std::cerr << "Key 'close' not found in numericData map." << std::endl;
            return "HOLD";
        }

        const auto& allClosePrices = numericData.at("close");

        if (allClosePrices.empty()) {
            std::cerr << "Close prices data is empty." << std::endl;
            return "HOLD";
        }

        for (const auto& price : allClosePrices) {
            prices.push_back(price);
            if (prices.size() > windowSize) prices.pop_front();
        }

        if (prices.size() == windowSize) {
            double mean = std::accumulate(prices.begin(), prices.end(), 0.0) / prices.size();
            double variance = std::accumulate(prices.begin(), prices.end(), 0.0,
                [&](double sum, double p) { return sum + (p - mean) * (p - mean); }) / prices.size();
            double stddev = std::sqrt(variance);

            std::cout << "Mean: " << mean << ", StdDev: " << stddev << ", Last Price: " << prices.back() << std::endl;

            if (prices.back() <= mean - threshold * stddev) {
                return "BUY";
            } else if (prices.back() >= mean + threshold * stddev) {
                return "SELL";
            }
        } else {
            std::cout << "Window size > total historical data." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in makeDecision: " << e.what() << std::endl;
    }

    return "HOLD";
}
