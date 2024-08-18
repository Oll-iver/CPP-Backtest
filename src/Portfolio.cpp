#include "Portfolio.hpp"
#include <algorithm>
#include <iostream>

// this file needs comments added to improve readability. 
//similar to both strategies, this file was added a lot and 
//like also has unneeded debugging.

Portfolio::Portfolio(double initialCash) : initialCash(initialCash), cashBalance(initialCash) {}

void Portfolio::addTrade(const Trade& trade) {
    openTrades.push_back(trade);
    cashBalance -= trade.getEntryPrice() * trade.getQuantity();
    std::cout << "Added trade: " << trade.getSymbol() << " at " << trade.getEntryPrice()
              << ", quantity: " << trade.getQuantity() << ", new cash balance: " << cashBalance << std::endl;
}

void Portfolio::closeTrade(const std::string& symbol, double exitPrice, int quantity, const std::string& exitDate) {
    auto tradeIt = findOpenTrade(symbol);
    if (tradeIt != openTrades.end()) {
        if (tradeIt->getQuantity() != quantity) {
            std::cerr << "Warning: Closing trade with mismatched quantity. Expected: " 
                      << tradeIt->getQuantity() << ", Provided: " << quantity << std::endl;
        }

        tradeIt->closeTrade(exitPrice, exitDate);
        cashBalance += exitPrice * quantity;  
        closedTrades.push_back(*tradeIt);
        openTrades.erase(tradeIt);
        std::cout << "Closed trade: " << symbol << " at " << exitPrice
                  << ", quantity: " << quantity << ", new cash balance: " << cashBalance << std::endl;
    } else {
        std::cerr << "Error: Attempting to close a trade that does not exist for symbol: " << symbol << std::endl;
    }
}


double Portfolio::getCashBalance() const {
    return cashBalance;
}

double Portfolio::getTotalValue(double currentPrice) const {
    double totalValue = cashBalance;
    for (const auto& trade : openTrades) {
        totalValue += currentPrice * trade.getQuantity();
    }
    return totalValue;
}

double Portfolio::getTotalProfitLoss() const {
    double totalProfitLoss = 0.0;
    for (const auto& trade : closedTrades) {
        totalProfitLoss += trade.getProfitLoss();
    }
    return totalProfitLoss;
}

std::vector<Trade>::iterator Portfolio::findOpenTrade(const std::string& symbol) {
    return std::find_if(openTrades.begin(), openTrades.end(), [&symbol](const Trade& trade) {
        return trade.getSymbol() == symbol;
    });
}
