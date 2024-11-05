#ifndef MEANREVERSIONSTRATEGY_HPP
#define MEANREVERSIONSTRATEGY_HPP

//Include necessary header files
#include "SimpleStrategy.hpp"
#include <deque>
#include <string>
#include <map>

//Class for implementing mean reversion trading strategy. 
class MeanReversionStrategy : public SimpleStrategy {
public:
    //Initialise default values
    MeanReversionStrategy();

    //Initialises strategy parameters, updates portfolio based on outcome of executing strategy.
    void initialize(const std::map<std::string, double>& params) override;
    void execute(Portfolio& portfolio, const std::map<std::string, double>& data) override;

    // Method to make a buy/sell decision based on the most recent price in a CSV file
    std::string makeDecision(const std::string& dataFilePath);

    // Check if a position is currently held
    bool isPositionHeld() const;

private:
    std::deque<double> prices; //Rolling window of recent prices to calculuate mean and variance
    int windowSize;
    double threshold;
    bool hasPosition;
};

#endif // MEANREVERSIONSTRATEGY_HPP
