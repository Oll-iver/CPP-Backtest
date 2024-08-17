#ifndef SIMPLESTRATEGY_HPP
#define SIMPLESTRATEGY_HPP

#include "Portfolio.hpp"
#include <map>
#include <string>

class SimpleStrategy {
public:
    virtual ~SimpleStrategy() = default;

    virtual void initialize(const std::map<std::string, double>& params) = 0;
    virtual void execute(Portfolio& portfolio, const std::map<std::string, double>& data) = 0;
};

#endif // SIMPLESTRATEGY_HPP
