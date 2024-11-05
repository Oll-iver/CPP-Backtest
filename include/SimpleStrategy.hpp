#ifndef SIMPLESTRATEGY_HPP
#define SIMPLESTRATEGY_HPP

//Include necessary header files
#include "Portfolio.hpp"
#include <map>
#include <string>

//Base class for trading strategies.
class SimpleStrategy {
public:
    //Virtual destructor allows for proper cleanup
    virtual ~SimpleStrategy() = default;

    //virtual method initialises strategy parameters and executes the strategy, updating portfolio
    virtual void initialize(const std::map<std::string, double>& params) = 0;
    virtual void execute(Portfolio& portfolio, const std::map<std::string, double>& data) = 0;
};

#endif // SIMPLESTRATEGY_HPP
