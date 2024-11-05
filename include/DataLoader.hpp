#ifndef DATALOADER_HPP
#define DATALOADER_HPP

//Include necessary headers
#include "Portfolio.hpp"
#include <map>
#include <vector>
#include <string>

//Class for loading data for backtesting incl market data and portfolio data
class DataLoader {
public:
    //Constructor initialising the data and portfolio file paths
    DataLoader(const std::string& dataFilePath, const std::string& portfolioFilePath);

    //Loads market data and portfolio data; populates portfolio object
    void loadData();
    void loadPortfolio(Portfolio& portfolio);

    // method to get the most recent row of market data
    std::map<std::string, double> getMostRecentData() const;

    //Separately retrieve numeric and string-based market data
    const std::map<std::string, std::vector<double>>& getNumericData() const;
    const std::map<std::string, std::vector<std::string>>& getStringData() const;

private:
    std::string dataFilePath;
    std::string portfolioFilePath; //File paths
    //Maps for storing data, keys are datatypes or asset names, values are lists of data points.
    std::map<std::string, std::vector<double>> numericData;
    std::map<std::string, std::vector<std::string>> stringData;
};

#endif // DATALOADER_HPP
