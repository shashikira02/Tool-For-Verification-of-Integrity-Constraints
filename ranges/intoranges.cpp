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
                columnOrder.push_back(column); // Store column names in the desired order
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
        std::string outputFilePath = inputFileName + "_output.txt";
        std::ofstream outputFile(outputFilePath);
        if (!outputFile.is_open()) {
            std::cerr << "Error: Cannot create output file." << std::endl;
            return;
        }

        // Sort columns based on desired order
        for (const auto& columnName : columnOrder) {
            const auto& columnPair = columnData[columnName];
            outputFile << inputFileName << "_" << columnName << "[" << columnPair.first << "," << columnPair.second << "]" << std::endl;
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
    static std::vector<std::string> columnOrder; // Vector to store the desired order of columns
};

std::map<std::string, int> TextFileAnalyzer::columnIndexes;
std::vector<std::string> TextFileAnalyzer::columnOrder;

int main() {
    //  std::chrono::steady_clock::time_point start_time, end_time;

    // // Record the start time
    // start_time = std::chrono::steady_clock::now();
    std::string inputFilePath = "C:\\Users\\ADMIN\\Desktop\\7th sem\\project\\New folder\\input.txt";  //input file path
    TextFileAnalyzer::processTextFile(inputFilePath);
    // // Record the end time
    // end_time = std::chrono::steady_clock::now();

    // // Calculate elapsed time
    // std::chrono::duration<double> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);

    // // Print the elapsed time
    // std::cout << "Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;
    return 0;
}
