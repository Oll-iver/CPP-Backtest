#include "BacktestEngine.hpp"
#include "SimpleStrategy.hpp"
#include "MovingAverageCrossoverStrategy.hpp"
#include <cassert>
#include <iostream>

void testBacktestEngine() {
    MovingAverageCrossoverStrategy strategy; 

    // Pass the strategy to BacktestEngine, which expects a SimpleStrategy pointer
    BacktestEngine engine("data/test_data.csv", "data/portfolio.csv",&strategy, 100000.0);
    engine.run();
    // No assertions here because the engine prints the results,
    // but you can capture and check the output or extend the engine to store results for verification.

    std::cout << "BacktestEngine test ran successfully!" << std::endl;
}

int main() {
    testBacktestEngine();
    return 0;
}
