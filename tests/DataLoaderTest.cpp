#include "DataLoader.hpp"
#include <cassert>
#include <iostream>

void testDataLoader() {
    DataLoader dataLoader("../data/test_data.csv");  // Adjust the path as necessary
    dataLoader.loadData();

    const auto& numericData = dataLoader.getNumericData();
    const auto& stringData = dataLoader.getStringData();

    // Assuming test_data.csv has headers: Date, Open, Close
    assert(numericData.find("Open") != numericData.end());
    assert(numericData.find("Close") != numericData.end());
    assert(stringData.find("Date") != stringData.end());
    assert(stringData.find("Symbol") != stringData.end());

    assert(numericData.at("Open").size() > 0);
    assert(numericData.at("Close").size() > 0);
    assert(stringData.at("Date").size() > 0);
    assert(stringData.at("Symbol").size() > 0);


    std::cout << "DataLoader tests passed!" << std::endl;
}

int main() {
    testDataLoader();
    return 0;
}
