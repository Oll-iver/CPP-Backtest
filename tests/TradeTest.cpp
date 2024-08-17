#include "Trade.hpp"
#include <cassert>
#include <iostream>

void testTrade() {
    Trade trade("AAPL", 150.0, 100, "2024-01-01");
    
    // Check initial values
    assert(trade.getSymbol() == "AAPL");
    assert(trade.getEntryPrice() == 150.0);
    assert(trade.getQuantity() == 100);
    assert(trade.getEntryDate() == "2024-01-01");

    // Close the trade and verify profit/loss
    trade.closeTrade(155.0, "2024-01-15");
    assert(trade.getExitPrice() == 155.0);
    assert(trade.getExitDate() == "2024-01-15");
    assert(trade.getProfitLoss() == 500.0); // (155 - 150) * 100

    std::cout << "Trade tests passed!" << std::endl;
}

int main() {
    testTrade();
    return 0;
}
