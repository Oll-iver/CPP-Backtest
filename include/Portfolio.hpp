#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

//Include necessary headers
#include "Trade.hpp"
#include <vector>
#include <string>

//Portfolio class
class Portfolio {
public:
    // Constructor
    Portfolio(double initialCash);

    // Method to add a trade
    void addTrade(const Trade& trade);

    // Method to close a trade
    void closeTrade(const std::string& symbol, double exitPrice, int quantity, const std::string& exitDate);

    // Getters for portfolio details
    double getCashBalance() const;
    double getTotalValue(double currentPrice) const;
    double getTotalProfitLoss() const;

private:
    double initialCash;                // Initial cash balance
    double cashBalance;                // Current cash balance
    std::vector<Trade> openTrades;     // Currently open trades
    std::vector<Trade> closedTrades;   // Completed trades

    // Helper method to find an open trade by symbol
    std::vector<Trade>::iterator findOpenTrade(const std::string& symbol);
};

#endif // PORTFOLIO_HPP
