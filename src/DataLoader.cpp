#include "DataLoader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

DataLoader::DataLoader(const std::string& dataFilePath, const std::string& portfolioFilePath)
    : dataFilePath(dataFilePath), portfolioFilePath(portfolioFilePath) {}

void DataLoader::loadData() {
    std::ifstream file(dataFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << dataFilePath << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);  // Read the header line
    std::istringstream headerStream(line);
    std::string header;
    std::vector<std::string> headers;

    // Parse headers
    while (std::getline(headerStream, header, ',')) {
        headers.push_back(header);
        if (header == "date" || header == "symbol") {
            stringData[header] = std::vector<std::string>();  // Initialize vector for string data
        } else {
            numericData[header] = std::vector<double>();  // Initialize vector for numeric data
        }
    }

    // Debug: Print out parsed headers
    std::cout << "Parsed headers:" << std::endl;
    for (const auto& h : headers) {
        std::cout << h << std::endl;
    }

    // Read data lines
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string cell;
        int columnIndex = 0;

        while (std::getline(lineStream, cell, ',')) {
            // Convert to double only if the cell is part of a numeric column
            if (headers[columnIndex] == "date" || headers[columnIndex] == "symbol") {
                stringData[headers[columnIndex]].push_back(cell);  // Store as string
            } else {
                try {
                    double value = std::stod(cell);
                    numericData[headers[columnIndex]].push_back(value);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument for std::stod: " << cell << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of range error for std::stod: " << cell << std::endl;
                }
            }
            columnIndex++;
        }
    }

    file.close();

    // Debug: Check if the maps are populated correctly
    std::cout << "String data loaded:" << std::endl;
    for (const auto& [key, vec] : stringData) {
        std::cout << key << ": " << vec.size() << " entries" << std::endl;
    }

    std::cout << "Numeric data loaded:" << std::endl;
    for (const auto& [key, vec] : numericData) {
        std::cout << key << ": " << vec.size() << " entries" << std::endl;
    }
}


// Method to load the portfolio from a CSV file
void DataLoader::loadPortfolio(Portfolio& portfolio) {
    std::ifstream file(portfolioFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open portfolio file: " << portfolioFilePath << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);  // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string symbol, date;
        double price;
        int quantity;

        std::getline(lineStream, symbol, ',');
        lineStream >> price;
        lineStream.ignore(1);  // Skip the comma
        lineStream >> quantity;
        lineStream.ignore(1);  // Skip the comma
        std::getline(lineStream, date, ',');

        portfolio.addTrade(Trade(symbol, price, quantity, date));
    }

    file.close();
    std::cout << "Portfolio loaded from " << portfolioFilePath << std::endl;
}

std::map<std::string, double> DataLoader::getMostRecentData() const {
    std::map<std::string, double> recentData;

    if (numericData.empty()) {
        std::cerr << "No numeric data available to retrieve the most recent data." << std::endl;
        return recentData;
    }

    // Assuming all columns have the same number of rows, we use the last index
    size_t lastIndex = numericData.begin()->second.size() - 1;

    // Fill the map with the most recent values
    for (const auto& entry : numericData) {
        recentData[entry.first] = entry.second[lastIndex];
    }

    return recentData;
}

const std::map<std::string, std::vector<double>>& DataLoader::getNumericData() const {
    return numericData;
}

const std::map<std::string, std::vector<std::string>>& DataLoader::getStringData() const {
    return stringData;
}
