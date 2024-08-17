#include "BacktestEngine.hpp"
#include "MovingAverageCrossoverStrategy.hpp" // Include your concrete strategy implementation
#include "Portfolio.hpp"

int main() {
    MovingAverageCrossoverStrategy strategy; // Instantiate the concrete strategy
    BacktestEngine engine("../data/test_data.csv", &strategy, 100000);
    engine.run();
    return 0;
}
