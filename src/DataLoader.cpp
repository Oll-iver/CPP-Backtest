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
    if (!std::getline(file, line)) {  // Read the header line
        std::cerr << "Failed to read the header line from the file." << std::endl;
        return;
    }
    std::istringstream headerStream(line);
    std::string header;
    std::vector<std::string> headers;

    // Parse headers
    while (std::getline(headerStream, header, ',')) {
        headers.push_back(header);
        std::cout << "Parsed header: " << header << std::endl;

        if (header == "date") {
            stringData[header] = std::vector<std::string>();
            std::cout << "Initialized stringData for key: " << header << std::endl;
        } else {
            numericData[header] = std::vector<double>();
            std::cout << "Initialized numericData for key: " << header << std::endl;
        }
    }

    // Read lines
    int lineNumber = 0;
    while (std::getline(file, line)) {
        lineNumber++;
        std::cout << "Reading line " << lineNumber << ": " << line << std::endl;

        std::istringstream lineStream(line);
        std::string cell;
        int columnIndex = 0;

        while (std::getline(lineStream, cell, ',')) {
            if (columnIndex >= headers.size()) {
                std::cerr << "Column index out of bounds: " << columnIndex << " on line " << lineNumber << std::endl;
                break;
            }

            const std::string& key = headers[columnIndex];
            std::cout << "Processing cell for key " << key << ": " << cell << std::endl;

            if (key == "date") {
                stringData[key].push_back(cell);
                std::cout << "Adding to stringData[" << key << "]: " << cell << std::endl;
            } else {
                try {
                    double value = std::stod(cell);
                    numericData[key].push_back(value);
                    std::cout << "Adding to numericData[" << key << "]: " << value << std::endl;
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument for std::stod: " << cell << " at column " << key << " on line " << lineNumber << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of range error for std::stod: " << cell << " at column " << key << " on line " << lineNumber << std::endl;
                }
            }
            columnIndex++;
        }
    }

    file.close();

    // Debug: Check if the maps are being initialised correctly
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

    int lineNumber = 1;  // To track the line number in the CSV file
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string symbol, date;
        double price;
        int quantity;

        try {
            if (!std::getline(lineStream, symbol, ',') || 
                !(lineStream >> price) || !lineStream.ignore(1) ||  // Skip comma
                !(lineStream >> quantity) || !lineStream.ignore(1) ||  
                !std::getline(lineStream, date, ',')) {
                
                throw std::runtime_error("Error parsing line " + std::to_string(lineNumber));
            }

            // Print confirmation before adding trade
            std::cout << "Adding trade to portfolio: "
                      << "Symbol=" << symbol << ", Price=" << price 
                      << ", Quantity=" << quantity << ", Date=" << date << std::endl;

            portfolio.addTrade(Trade(symbol, price, quantity, date));
        } catch (const std::exception& e) {
            std::cerr << "Exception while parsing portfolio CSV: " << e.what() << std::endl;
        }

        lineNumber++;
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

    size_t lastIndex = numericData.begin()->second.size() - 1;

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
