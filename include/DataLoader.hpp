#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>

class DataLoader {
public:
    DataLoader(const std::string& filePath);

    void loadData();

    const std::map<std::string, std::vector<double>>& getNumericData() const;
    const std::map<std::string, std::vector<std::string>>& getStringData() const;

private:
    std::string filePath;
    std::map<std::string, std::vector<double>> numericData;
    std::map<std::string, std::vector<std::string>> stringData;
};

#endif // DATALOADER_HPP
