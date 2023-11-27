#include <bits/stdc++.h>

using namespace std;

class TextFileAnalyzer {
public:
    static void processTextFile(const std::string& inputFilePath) {
        std::string inputFileName = getFileName(inputFilePath);
        std::ifstream inputFile(inputFilePath);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Cannot open input file." << std::endl;
            return;
        }

        std::map<std::string, std::pair<int, int>> columnData;  // Map to store column data and its range
        std::string headerLine;
        std::string line;

        if (std::getline(inputFile, headerLine)) {
            std::istringstream headerStream(headerLine);
            std::string column;
            int columnNumber = 0;
            while (headerStream >> column) {
                columnData[column] = {std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};
                columnIndexes[column] = columnNumber;
                columnNumber++;
            }
        }

        // Process data lines
        while (std::getline(inputFile, line)) {
            std::istringstream lineStream(line);
            int columnValue;
            int columnNumber = 0;
            while (lineStream >> columnValue) {
                const std::string columnName = getColumnForIndex(columnNumber);
                columnData[columnName].first = std::min(columnData[columnName].first, columnValue);
                columnData[columnName].second = std::max(columnData[columnName].second, columnValue);
                columnNumber++;
            }
        }

        inputFile.close();  // Closing the input file

        // Write output to file
        std::string outputFilePath =  "LIout.txt";
        std::ofstream outputFile(outputFilePath);
        if (!outputFile.is_open()) {
            std::cerr << "Error: Cannot create output file." << std::endl;
            return;
        }

        for (const auto& columnPair : columnData) {
            const std::string& columnName = columnPair.first;
            int minVal = columnPair.second.first;
            int maxVal = columnPair.second.second;
            
            // Write inequalities in the desired format
            outputFile << inputFileName << "_" << columnName << ">=" << minVal << ",-" << inputFileName << "_" << columnName << ">=-" << maxVal << std::endl;
        }

        outputFile.close();
        std::cout << "Output written to " << outputFilePath << std::endl;
    }

private:
    static std::string getFileName(const std::string& filePath) {
        size_t lastSlash = filePath.find_last_of("/\\");
        size_t lastDot = filePath.find_last_of(".");
        if (lastDot == std::string::npos || lastDot < lastSlash) {
            lastDot = filePath.length();
        }
        return filePath.substr(lastSlash + 1, lastDot - lastSlash - 1);
    }
    
    static std::string getColumnForIndex(int index) {
        for (const auto& pair : columnIndexes) {
            if (pair.second == index) {
                return pair.first;
            }
        }
        return "";
    }

    static std::map<std::string, int> columnIndexes;  // Map to store column names and their corresponding indexes
};

std::map<std::string, int> TextFileAnalyzer::columnIndexes;

int main() {
    std::string inputFilePath = "input2.txt";  //input file path
    TextFileAnalyzer::processTextFile(inputFilePath);
    return 0;
}
