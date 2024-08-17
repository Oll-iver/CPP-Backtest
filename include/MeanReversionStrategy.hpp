#ifndef MEANREVERSIONSTRATEGY_HPP
#define MEANREVERSIONSTRATEGY_HPP

#include "SimpleStrategy.hpp"
#include <deque>
#include <string>
#include <map>

class MeanReversionStrategy : public SimpleStrategy {
public:
    MeanReversionStrategy();

    void initialize(const std::map<std::string, double>& params) override;
    void execute(Portfolio& portfolio, const std::map<std::string, double>& data) override;
    // New method to make a decision based on the most recent price in a CSV file
    std::string makeDecision(const std::string& dataFilePath);

    // Check if a position is currently held
    bool isPositionHeld() const;

private:
    std::deque<double> prices;
    int windowSize;
    double threshold;
    bool hasPosition;
};

#endif // MEANREVERSIONSTRATEGY_HPP
