#ifndef MOVING_AVERAGE_CROSSOVER_STRATEGY_HPP
#define MOVING_AVERAGE_CROSSOVER_STRATEGY_HPP

#include "SimpleStrategy.hpp"
#include <deque>

class MovingAverageCrossoverStrategy : public SimpleStrategy {
public:
    void initialize(const std::map<std::string, double>& params) override;
    void execute(Portfolio& portfolio, const std::map<std::string, double>& data, bool hasPosition) override;

private:
    int shortWindow = 0;
    int longWindow = 0;
    std::deque<double> shortPrices;
    std::deque<double> longPrices;
};

#endif // MOVING_AVERAGE_CROSSOVER_STRATEGY_HPP
