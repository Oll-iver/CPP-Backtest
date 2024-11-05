#ifndef MOVINGAVERAGECROSSOVERSTRATEGY_HPP
#define MOVINGAVERAGECROSSOVERSTRATEGY_HPP

//Include necessary header files
#include "SimpleStrategy.hpp"
#include <deque>
#include <iostream>

//Class implements moving average crossover strategy. very simple.
class MovingAverageCrossoverStrategy : public SimpleStrategy {
public:
    //Constructor to intialise default values.
    MovingAverageCrossoverStrategy();

    //Initialises strategy parameters, executes strategy, updates portfolio based on execution outcome.
    void initialize(const std::map<std::string, double>& params) override;
    void execute(Portfolio& portfolio, const std::map<std::string, double>& data) override;
    //Makes a buy/sell decision on the most recent prices.
    std::string makeDecision(const std::string& dataFilePath);

    bool isPositionHeld() const;
private:
    std::deque<double> shortPrices; //Window of prices for short MA
    std::deque<double> longPrices; //As above
    int shortWindow;
    int longWindow;
    bool hasPosition;
};

#endif // MOVINGAVERAGECROSSOVERSTRATEGY_HPP
