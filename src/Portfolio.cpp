#include "Portfolio.hpp"
#include <algorithm>
#include <iostream>

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
        // Ensure the quantity matches or adjust accordingly if needed
        tradeIt->closeTrade(exitPrice, exitDate);
        cashBalance += exitPrice * quantity;  // Add the proceeds from selling the shares to the cash balance
        closedTrades.push_back(*tradeIt);
        openTrades.erase(tradeIt);
        std::cout << "Closed trade: " << symbol << " at " << exitPrice
                  << ", quantity: " << quantity << ", new cash balance: " << cashBalance << std::endl;
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
