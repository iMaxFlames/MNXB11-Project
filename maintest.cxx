#include "include/UMEA.h"
#include <iostream>
#include <fstream>
#include <algorithm>

int main() {
    CSVReader reader("datasets/rawdata_smhi-opendata_1_140480_20231007_155326_Umea.csv");

    if (reader.readCSV()) {
        std::vector<std::vector<std::string>> data = reader.getData();

        // Iterate through the vector in reverse order to safely remove elements
        for (int i = data.size() - 1; i >= 0; --i) {
            // Check if the last column of the row contains "Y"
            if (data[i].back() == "Y") {
                // Remove the row if the condition is met
                data.erase(data.begin() + i);
            }
        }

        // Print the cleaned data to a new file
        std::ofstream outputFile("datasets/cleanedData.csv");
        if (outputFile.is_open()) {
            for (const auto &row : data) {
                for (size_t j = 0; j < row.size(); ++j) {
                    outputFile << row[j];
                    if (j < row.size() - 1) {
                        outputFile << ",";
                    }
                }
                outputFile << "\n";
            }
            outputFile.close();
            std::cout << "Cleaned data saved to 'datasets/cleanedData.csv'" << std::endl;
        } else {
            std::cerr << "Error opening output file." << std::endl;
        }
    }

    return 0;
}