#ifndef BACKTESTENGINE_HPP
#define BACKTESTENGINE_HPP

#include <string>
#include "DataLoader.hpp"
#include "SimpleStrategy.hpp"
#include "Portfolio.hpp"

//Class representing the backtesting engine itself
class BacktestEngine {
public:
    BacktestEngine(const std::string& dataFilePath, const std::string& portfolioFilePath, SimpleStrategy* strategy, double initialCash);

    void run();

private:
    //Dataloader object, pointer to strategy being tested, portfolio object
    DataLoader dataLoader;
    SimpleStrategy* strategy;
    Portfolio portfolio;
};

#endif // BACKTESTENGINE_HPP
