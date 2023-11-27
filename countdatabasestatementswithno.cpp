#include <bits/stdc++.h>
#include <iostream>
#include <chrono>

using namespace std;



class CountDatabaseStatements {
public:
    static int main(const std::string& inputFilePath, std::vector<std::string>& databaseStatements) {
        int numberOfDatabaseStatements = 0;
        int statementNumber = 1;  // Initialize the statement number

        try {
            std::ifstream inputFile(inputFilePath);
            std::string line;
            std::string statementBuffer;
            bool insideStatement = false;

            while (std::getline(inputFile, line)) {
            
                if (!insideStatement) {
                    if (isStartOfDatabaseStatement(line)) {
                        insideStatement = true;
                        statementBuffer = "Statement " + std::to_string(statementNumber++) + ":\n" + line;
                    }
                } else {

                    statementBuffer += "\n" + line;
                    if (isEndOfDatabaseStatement(line)) {
                        insideStatement = false;
                        numberOfDatabaseStatements++;
                        databaseStatements.push_back(statementBuffer);
                    }
                }
            }

            inputFile.close();  // Close the input file after use
        } catch (const std::exception& e) {  // Handle exceptions
            std::cerr << "Error: " << e.what() << std::endl;
        }
        return numberOfDatabaseStatements;
    }

    static bool isStartOfDatabaseStatement(const std::string& line) {
    
          std::regex update_regex(R"(\bUPDATE\s+\w+\s+SET\b)", std::regex_constants::icase);
    std::regex delete_regex(R"(\bDELETE\s+FROM\b)", std::regex_constants::icase);
    std::regex insert_regex(R"(\bINSERT\s+INTO\b)", std::regex_constants::icase);
    std::regex select_regex(R"(\bSELECT\b)", std::regex_constants::icase);
    

       if (std::regex_search(line, update_regex)) {

            return true;
        }
        if (std::regex_search(line, delete_regex )) {
 
            return true;
        }
        if (std::regex_search(line, insert_regex )) {
  
            return true;
        }
        if (std::regex_search(line, select_regex)) {

            return true;
        }

        std::string lowerCaseLine = line;

        std::transform(lowerCaseLine.begin(), lowerCaseLine.end(), lowerCaseLine.begin(), ::tolower);

        return false ; 
    }

    static bool isEndOfDatabaseStatement(const std::string& line) {
         bool yes = false;
         for(auto it : line)
         {
            if(it == ';')
            {
                  yes = true; break;
            }
         }
         return yes;
    }

    static void writeDatabaseStatementsToFile(const std::string& outputFilePath, const std::vector<std::string>& databaseStatements) {
    try {
        std::ofstream outputFile(outputFilePath);
        for (const std::string& statement : databaseStatements) {
            size_t statementNumberPos = statement.find(":");
            std::string cleanedStatement = statement.substr(statementNumberPos + 2); 

            outputFile << cleanedStatement << "\n\n";
        }
        outputFile.close();
        std::cout << "Database statements written to " << outputFilePath << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

};

int main() {

    std::string inputFilePath = "./../uploads/benchmark.jsp";
    std::string outputFilePath = "output_database_statements.txt";  

    std::vector<std::string> databaseStatements;
    int count = CountDatabaseStatements::main(inputFilePath, databaseStatements);

    std::cout << "Number of database statements: " << count << std::endl;

    CountDatabaseStatements::writeDatabaseStatementsToFile(outputFilePath, databaseStatements);

    return 0;
}
