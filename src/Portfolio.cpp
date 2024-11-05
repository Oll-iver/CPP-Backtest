#include "Portfolio.hpp"
#include <algorithm>
#include <iostream>

//Initialise portfolio with an initial cash balance.
Portfolio::Portfolio(double initialCash) 
    : initialCash(initialCash), cashBalance(initialCash) {}

//Adds new trade to portfoilo, updating cash balance.
void Portfolio::addTrade(const Trade& trade) {
    openTrades.push_back(trade);
    cashBalance -= trade.getEntryPrice() * trade.getQuantity();
}

//Closes an open trade, updating cash balance
void Portfolio::closeTrade(const std::string& symbol, double exitPrice, int quantity, const std::string& exitDate) {
    auto tradeIt = findOpenTrade(symbol); //Use symbol to find open trade
    if (tradeIt != openTrades.end()) { //Check trade exists
        //Check quantity to close is compatible with the open trade's quantity
        if (tradeIt->getQuantity() != quantity) {
            std::cerr << "Warning: Closing trade with mismatched quantity. Expected: " 
                      << tradeIt->getQuantity() << ", Provided: " << quantity << std::endl;
        }

        //Close trade, update cash balance, move to closed trades.
        tradeIt->closeTrade(exitPrice, exitDate);
        cashBalance += exitPrice * quantity;  
        closedTrades.push_back(*tradeIt);
        openTrades.erase(tradeIt);
    } else { //If trade to close does not exist
        std::cerr << "Error: Attempting to close a trade that does not exist for symbol: " << symbol << std::endl;
    }
}

//Returns current cash balance
double Portfolio::getCashBalance() const {
    return cashBalance;
}

//Calculates total portfolio value
double Portfolio::getTotalValue(double currentPrice) const {
    double totalValue = cashBalance;
    for (const auto& trade : openTrades) {
        totalValue += currentPrice * trade.getQuantity();
    }
    return totalValue;
}

//Calculates total profit or loss from closed trades
double Portfolio::getTotalProfitLoss() const {
    double totalProfitLoss = 0.0;
    for (const auto& trade : closedTrades) {
        totalProfitLoss += trade.getProfitLoss();
    }
    return totalProfitLoss;
}

//Helper function to find open trade by symbol
std::vector<Trade>::iterator Portfolio::findOpenTrade(const std::string& symbol) {
    return std::find_if(openTrades.begin(), openTrades.end(), [&symbol](const Trade& trade) {
        return trade.getSymbol() == symbol;
    });
}
