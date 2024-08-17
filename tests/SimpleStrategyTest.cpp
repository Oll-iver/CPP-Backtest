#include "SimpleStrategy.hpp"
#include <cassert>
#include <iostream>

void testSimpleStrategy() {
    Portfolio portfolio(100000);
    SimpleStrategy strategy;

    std::map<std::string, double> data1 = {{"Open", 150.0}, {"Close", 155.0}, {"Date", 20240101}};
    std::map<std::string, double> data2 = {{"Open", 155.0}, {"Close", 150.0}, {"Date", 20240102}};

    strategy.execute(portfolio, data1);
    assert(portfolio.getCashBalance() == 85000.0); // 100000 - (150 * 10)

    strategy.execute(portfolio, data2);
    assert(portfolio.getCashBalance() == 100500.0); // 85000 + (155 * 10)
    assert(portfolio.getTotalProfitLoss() == 500.0); // (155 - 150) * 10

    std::cout << "SimpleStrategy tests passed!" << std::endl;
}

int main() {
    testSimpleStrategy();
    return 0;
}
