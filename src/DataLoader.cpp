#include "DataLoader.hpp"
#include <iostream>

DataLoader::DataLoader(const std::string& filePath) : filePath(filePath) {}

void DataLoader::loadData() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
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
        if (header == "Date" || header == "Symbol") {
            stringData[header] = std::vector<std::string>();  // Initialize vector for string data
        } else {
            numericData[header] = std::vector<double>();  // Initialize vector for numeric data
        }
    }

    // Read data lines
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string cell;
        int columnIndex = 0;

        while (std::getline(lineStream, cell, ',')) {
            // Debug: Print the cell being processed
            std::cout << "Processing cell: " << cell << std::endl;

            // Convert to double only if the cell is part of a numeric column
            if (headers[columnIndex] == "Date" || headers[columnIndex] == "Symbol") {
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
}

const std::map<std::string, std::vector<double>>& DataLoader::getNumericData() const {
    return numericData;
}

const std::map<std::string, std::vector<std::string>>& DataLoader::getStringData() const {
    return stringData;
}
