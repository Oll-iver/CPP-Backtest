#include "BacktestEngine.hpp"
#include "SimpleStrategy.hpp"
#include <cassert>
#include <iostream>

void testBacktestEngine() {
    SimpleStrategy strategy;
    BacktestEngine engine("path/to/your/test_data.csv", &strategy, 100000);

    engine.run();

    // No assertions here because the engine prints the results,
    // but you can capture and check the output or extend the engine to store results for verification.

    std::cout << "BacktestEngine test ran successfully!" << std::endl;
}

int main() {
    testBacktestEngine();
    return 0;
}
