#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "Portfolio.hpp"
#include <map>
#include <string>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void initialize(const std::map<std::string, double>& params) = 0;
    virtual void execute(Portfolio& portfolio, const std::map<std::string, double>& data, bool hasPosition) = 0;
};

#endif // STRATEGY_HPP
