#ifndef MEAN_REVERSION_STRATEGY_HPP
#define MEAN_REVERSION_STRATEGY_HPP

#include "SimpleStrategy.hpp"
#include <deque>

class MeanReversionStrategy : public SimpleStrategy {
public:
    void initialize(const std::map<std::string, double>& params) override;
    void execute(Portfolio& portfolio, const std::map<std::string, double>& data, bool hasPosition) override;

private:
    int windowSize = 0;
    double threshold = 0.0;
    std::deque<double> prices;
};

#endif // MEAN_REVERSION_STRATEGY_HPP
