#include "Portfolio.hpp"
#include <cassert>
#include <iostream>

void testPortfolio() {
    Portfolio portfolio(100000); // $100,000 initial cash

    Trade trade1("AAPL", 150.0, 100, "2024-01-01");
    portfolio.addTrade(trade1);
    assert(portfolio.getCashBalance() == 85000.0); // 100000 - (150 * 100)

    portfolio.closeTrade("AAPL", 155.0, 100, "2024-01-15");
    assert(portfolio.getCashBalance() == 100500.0); // 85000 + (155 * 100)
    assert(portfolio.getTotalProfitLoss() == 500.0); // (155 - 150) * 100

    std::cout << "Portfolio tests passed!" << std::endl;
}

int main() {
    testPortfolio();
    return 0;
}
