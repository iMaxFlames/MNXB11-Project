#include "include/UMEA.h"
#include <fstream>
#include <iostream>






/*
CSVReader::CSVReader(const std::string &filename) : filename(filename) {}

bool CSVReader::readCSV() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        size_t position = 0;
        std::string token;
        while ((position = line.find(',')) != std::string::npos) {
            token = line.substr(0, position);
            row.push_back(token);
            line.erase(0, position + 1);
        }
        row.push_back(line);
        data.push_back(row);
    }

    file.close();
    return true;
}

std::vector<std::vector<std::string>> CSVReader::getData() const {
    return data;
}
*/