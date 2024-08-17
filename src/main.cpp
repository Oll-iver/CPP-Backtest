#include <iostream>
#include <limits>
#include "BacktestEngine.hpp"
#include "MeanReversionStrategy.hpp"
#include "MovingAverageCrossoverStrategy.hpp"

int main() {
    // Ask the user to choose the strategy
    int strategyChoice;
    std::cout << "Choose the strategy to use:\n";
    std::cout << "1. Mean Reversion Strategy\n";
    std::cout << "2. Moving Average Crossover Strategy\n";
    std::cin >> strategyChoice;

    while (std::cin.fail() || (strategyChoice != 1 && strategyChoice != 2)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter 1 for Mean Reversion or 2 for Moving Average Crossover: ";
        std::cin >> strategyChoice;
    }

    // Get the initial cash amount
    double initialCash;
    std::cout << "Enter the total amount of money for your portfolio: ";
    std::cin >> initialCash;

    while (std::cin.fail() || initialCash <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a positive number: ";
        std::cin >> initialCash;
    }

    SimpleStrategy* strategy = nullptr; // Pointer to the selected strategy

    if (strategyChoice == 1) {
        // Get parameters for Mean Reversion Strategy
        int windowSize;
        std::cout << "Enter the window size for the mean reversion strategy: ";
        std::cin >> windowSize;

        while (std::cin.fail() || windowSize <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive number: ";
            std::cin >> windowSize;
        }

        double threshold;
        std::cout << "Enter the threshold for the mean reversion strategy: ";
        std::cin >> threshold;

        while (std::cin.fail() || threshold <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive number: ";
            std::cin >> threshold;
        }

        // Initialize Mean Reversion Strategy
        auto* meanReversionStrategy = new MeanReversionStrategy();
        meanReversionStrategy->initialize({{"windowSize", windowSize}, {"threshold", threshold}});
        strategy = meanReversionStrategy;
    } else if (strategyChoice == 2) {
        // Get parameters for Moving Average Crossover Strategy
        int shortWindow;
        std::cout << "Enter the short window size for the moving average crossover strategy: ";
        std::cin >> shortWindow;

        while (std::cin.fail() || shortWindow <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive number: ";
            std::cin >> shortWindow;
        }

        int longWindow;
        std::cout << "Enter the long window size for the moving average crossover strategy: ";
        std::cin >> longWindow;

        while (std::cin.fail() || longWindow <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive number: ";
            std::cin >> longWindow;
        }

        // Initialize Moving Average Crossover Strategy
        auto* movingAverageCrossoverStrategy = new MovingAverageCrossoverStrategy();
        movingAverageCrossoverStrategy->initialize({{"shortWindow", shortWindow}, {"longWindow", longWindow}});
        strategy = movingAverageCrossoverStrategy;
    }

    // Initialize and run the backtest engine with the selected strategy
    BacktestEngine engine("data/test_data.csv", "data/portfolio.csv", strategy, initialCash);
    engine.run();

    // Make a decision based on the most recent price
    std::string decision;
    if (strategyChoice == 1) {
        decision = static_cast<MeanReversionStrategy*>(strategy)->makeDecision("data/test_data.csv");
    } else if (strategyChoice == 2) {
        decision = static_cast<MovingAverageCrossoverStrategy*>(strategy)->makeDecision("data/test_data.csv");
    }
    std::cout << "Decision based on the most recent price: " << decision << std::endl;

    delete strategy;  // Clean up dynamically allocated strategy
    return 0;
}
