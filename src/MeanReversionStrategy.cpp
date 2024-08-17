#include "MeanReversionStrategy.hpp"
#include <numeric>
#include <iostream>

void MeanReversionStrategy::initialize(const std::map<std::string, double>& params) {
    windowSize = params.at("windowSize");
    threshold = params.at("threshold");
    std::cout << "Initialized with windowSize = " << windowSize << ", threshold = " << threshold << std::endl;
}

void MeanReversionStrategy::execute(Portfolio& portfolio, const std::map<std::string, double>& data, bool hasPosition) {
    double priceOpen = data.at("Open");
    double priceClose = data.at("Close");
    std::cout << hasPosition << "VALUE OF HAS POSITION";

    prices.push_back(priceOpen);
    if (prices.size() > windowSize) prices.pop_front();

    if (prices.size() == windowSize) {
        double average = std::accumulate(prices.begin(), prices.end(), 0.0) / windowSize;
        std::cout << "Price: " << priceOpen << ", Average: " << average << std::endl;
        if (hasPosition == 1){
            if (priceOpen > average + threshold){
                std::cout<<"REACHING THIS POINT.";
                portfolio.closeTrade("AAPL", priceClose, 100, "2024-01-15");
                hasPosition = false;
                std::cout << "Sold at " << priceClose << std::endl;
            }
            else{
                std::cout << "has position is right but the prices aren't";
            }
        }
        else if (priceOpen < average - threshold) {
            portfolio.addTrade(Trade("AAPL", priceOpen, 100, "2024-01-01"));
            hasPosition = true;
            std::cout << "Bought at " << priceOpen << std::endl;
        } 
        else if (priceOpen > average + threshold && hasPosition) {

        }
    }
}
