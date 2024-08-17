#ifndef SIMPLESTRATEGY_HPP
#define SIMPLESTRATEGY_HPP

#include "Strategy.hpp"

class SimpleStrategy : public Strategy {
public:
    void initialize(const std::map<std::string, double>& params) override {}
    virtual void execute(Portfolio& portfolio, const std::map<std::string, double>& data, bool hasPosition) = 0;
};

#endif // SIMPLESTRATEGY_HPP
