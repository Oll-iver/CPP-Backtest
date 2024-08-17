#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include "Portfolio.hpp"
#include <map>
#include <vector>
#include <string>

class DataLoader {
public:
    DataLoader(const std::string& dataFilePath, const std::string& portfolioFilePath);

    void loadData();
    void loadPortfolio(Portfolio& portfolio);

    // New function to get the most recent data row
    std::map<std::string, double> getMostRecentData() const;

    const std::map<std::string, std::vector<double>>& getNumericData() const;
    const std::map<std::string, std::vector<std::string>>& getStringData() const;

private:
    std::string dataFilePath;
    std::string portfolioFilePath;
    std::map<std::string, std::vector<double>> numericData;
    std::map<std::string, std::vector<std::string>> stringData;
};

#endif // DATALOADER_HPP
