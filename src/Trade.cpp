#include "Trade.hpp"

//add comments to improve readability

Trade::Trade(const std::string& symbol, double entryPrice, int quantity, const std::string& entryDate)
    : symbol(symbol), entryPrice(entryPrice), exitPrice(0.0), quantity(quantity), entryDate(entryDate), exitDate(""), profitLoss(0.0) {}

void Trade::closeTrade(double exitPrice, const std::string& exitDate) {
    this->exitPrice = exitPrice;
    this->exitDate = exitDate;
    profitLoss = (exitPrice - entryPrice) * quantity;
}

const std::string& Trade::getSymbol() const { return symbol; }
double Trade::getEntryPrice() const { return entryPrice; }
double Trade::getExitPrice() const { return exitPrice; }
int Trade::getQuantity() const { return quantity; }
const std::string& Trade::getEntryDate() const { return entryDate; }
const std::string& Trade::getExitDate() const { return exitDate; }
double Trade::getProfitLoss() const { return profitLoss; }
