#ifndef MOVINGAVERAGECROSSOVERSTRATEGY_HPP
#define MOVINGAVERAGECROSSOVERSTRATEGY_HPP

#include "SimpleStrategy.hpp"
#include <deque>
#include <iostream>

class MovingAverageCrossoverStrategy : public SimpleStrategy {
public:
    MovingAverageCrossoverStrategy();

    void initialize(const std::map<std::string, double>& params) override;
    void execute(Portfolio& portfolio, const std::map<std::string, double>& data) override;
    std::string makeDecision(const std::string& dataFilePath);

    bool isPositionHeld() const;
private:
    std::deque<double> shortPrices;
    std::deque<double> longPrices;
    int shortWindow;
    int longWindow;
    bool hasPosition;
};

#endif // MOVINGAVERAGECROSSOVERSTRATEGY_HPP
