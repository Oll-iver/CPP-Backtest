#ifndef BACKTESTENGINE_HPP
#define BACKTESTENGINE_HPP

#include <string>
#include "DataLoader.hpp"
#include "SimpleStrategy.hpp"
#include "Portfolio.hpp"

class BacktestEngine {
public:
    BacktestEngine(const std::string& dataFilePath, const std::string& portfolioFilePath, SimpleStrategy* strategy, double initialCash);

    void run();

private:
    DataLoader dataLoader;
    SimpleStrategy* strategy;
    Portfolio portfolio;
};

#endif // BACKTESTENGINE_HPP
