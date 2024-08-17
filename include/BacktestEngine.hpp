#ifndef BACKTESTENGINE_HPP
#define BACKTESTENGINE_HPP

#include "Strategy.hpp"
#include "Portfolio.hpp"
#include "DataLoader.hpp"

class BacktestEngine {
public:
    BacktestEngine(const std::string& dataFilePath, Strategy* strategy, double initialCash);

    void run();

private:
    DataLoader dataLoader;
    Portfolio portfolio;
    Strategy* strategy;
};

#endif // BACKTESTENGINE_HPP
