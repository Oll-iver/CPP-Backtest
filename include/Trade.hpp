#ifndef TRADE_HPP
#define TRADE_HPP

#include <string>

class Trade {
public:
    // Constructor
    Trade(const std::string& symbol, double entryPrice, int quantity, const std::string& entryDate);

    // Method to close the trade
    void closeTrade(double exitPrice, const std::string& exitDate);

    // Getters for trade details
    const std::string& getSymbol() const;
    double getEntryPrice() const;
    double getExitPrice() const;
    int getQuantity() const;
    const std::string& getEntryDate() const;
    const std::string& getExitDate() const;
    double getProfitLoss() const;

private:
    std::string symbol;        // Asset symbol
    double entryPrice;         // Entry price
    double exitPrice;          // Exit price
    int quantity;              // Quantity of the asset
    std::string entryDate;     // Date of entry
    std::string exitDate;      // Date of exit
    double profitLoss;         // Profit or loss of the trade
};

#endif // TRADE_HPP
