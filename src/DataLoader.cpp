#include "DataLoader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

//Initialise dataloader with paths to data and portfolio
DataLoader::DataLoader(const std::string& dataFilePath, const std::string& portfolioFilePath)
    : dataFilePath(dataFilePath), portfolioFilePath(portfolioFilePath) {}


void DataLoader::loadData() {
    //Open the data file for reading
    std::ifstream file(dataFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << dataFilePath << std::endl;
        return;
    }

    //Read header line
    std::string line;
    if (!std::getline(file, line)) { 
        std::cerr << "Failed to read the header line from the file." << std::endl;
        return;
    }

    //Parse column headers to get datatype
    std::istringstream headerStream(line);
    std::string header;
    std::vector<std::string> headers;

    //Identify each column as numeric or string based on header.
    while (std::getline(headerStream, header, ',')) {
        headers.push_back(header);
        std::cout << "Parsed header: " << header << std::endl;

        if (header == "date") {
            stringData[header] = std::vector<std::string>(); //String data
        } else {
            numericData[header] = std::vector<double>(); //Numeric data
        }
    }

    //Read each line of data after the header.
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string cell;
        int columnIndex = 0;

        //Parse each cell in the row based on column data type
        while (std::getline(lineStream, cell, ',')) {
            if (columnIndex >= headers.size()) {
                std::cerr << "Column index out of bounds: " << columnIndex << std::endl;
                break;
            }

            const std::string& key = headers[columnIndex];

            if (key == "date") { //Add date values of StringData
                stringData[key].push_back(cell);
            } else { //Add numeric values to numericData with error handling.
                try {
                    double value = std::stod(cell);
                    numericData[key].push_back(value);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid number format " << cell << " at column " << key << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of range number " << cell << " at column " << key << std::endl;
                }
            }
            columnIndex++;
        }
    }

    file.close();
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

    //Read each line to add trades
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string symbol, date;
        double price;
        int quantity;

        //Parse each trade entry with error handling
        try {
            if (!std::getline(lineStream, symbol, ',') || 
                !(lineStream >> price) || !lineStream.ignore(1) ||  // Skip comma
                !(lineStream >> quantity) || !lineStream.ignore(1) ||  
                !std::getline(lineStream, date, ',')) {
                
                throw std::runtime_error("Error parsing portfolio line");
            }
            //Add parsed trade to portfolio
            portfolio.addTrade(Trade(symbol, price, quantity, date));
        } catch (const std::exception& e) {
            std::cerr << "Exception while parsing portfolio CSV: " << e.what() << std::endl;
        }

    }

    file.close();
}

//Get most recent numeric data row
std::map<std::string, double> DataLoader::getMostRecentData() const {
    std::map<std::string, double> recentData;

    //Check numeric data exists
    if (numericData.empty()) {
        std::cerr << "No numeric data available to retrieve the most recent data." << std::endl;
        return recentData;
    }

    //Get last entry for each numeric data column
    size_t lastIndex = numericData.begin()->second.size() - 1;
    for (const auto& entry : numericData) {
        recentData[entry.first] = entry.second[lastIndex];
    }

    return recentData;
}

//Accessors for numeric and string data
const std::map<std::string, std::vector<double>>& DataLoader::getNumericData() const {
    return numericData;
}

const std::map<std::string, std::vector<std::string>>& DataLoader::getStringData() const {
    return stringData;
}
