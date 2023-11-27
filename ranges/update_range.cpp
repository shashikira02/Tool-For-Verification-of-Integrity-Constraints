#include <bits/stdc++.h>

using namespace std;

// Define a structure to hold the range information
struct Range {
    int min_val;
    int max_val;
};

// Constants for error messages
const string ERROR_OPEN_FILE = "Error: Cannot open file at path ";
const string ERROR_INVALID_FORMAT = "Error: Invalid format in input file.";
const string ERROR_INVALID_STATEMENT = "Error: Invalid statement: ";
const string WARNING_UNRECOGNIZED_STATEMENT = "Warning: Unrecognized statement type: ";
const string ERROR_RANGE_NOT_FOUND = "Error: filename_attribute not found in rangeMap.";
const string ERROR_INVALID_INTEGER_VALUE = "Error: Invalid integer value in statement.";

// Function to validate a statement
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

bool validateStatement(const string& statement) {
    // Define a list of valid operation keywords in lowercase
    vector<string> validKeywords = {"select", "update", "delete", "insert"};

    // Convert the statement to lowercase for comparison
    string lowerStatement = toLowerCase(statement);

    // Check if the lowercase statement contains any of the valid operation keywords
    for (const string& keyword : validKeywords) {
        if (lowerStatement.find(keyword) != string::npos) {
            return true; // The statement is considered valid
        }
    }

    return false; // The statement is considered invalid
}

// Function to read and parse the range input file
map<string, Range> readRangeInputFile(const string& filePath) {
    map<string, Range> rangeMap; // Map to store filename_attribute and its range

    ifstream rangeFile(filePath);
    if (!rangeFile.is_open()) {
        cerr << ERROR_OPEN_FILE << filePath << endl;
        return rangeMap;
    }

    string line;
    while (getline(rangeFile, line)) {
        // Check if the line has the expected format
        if (line.empty() || line.find("[") == string::npos || line.find("]") == string::npos) {
            cerr << ERROR_INVALID_FORMAT << endl;
            continue; // Skip this line and continue with the next one
        }

        // Extract the filename_attribute from the line
        size_t startPos = line.find_first_not_of(" "); // Find the first non-space character
        size_t endPos = line.find("[");
        string filename_attribute = line.substr(startPos, endPos - startPos);

        // Extract the min_val and max_val from the line
        startPos = line.find("[") + 1;
        endPos = line.find("]");
        string rangeStr = line.substr(startPos, endPos - startPos);

        // Split the range string into min_val and max_val
        size_t commaPos = rangeStr.find(",");
        string minValStr = rangeStr.substr(0, commaPos);
        string maxValStr = rangeStr.substr(commaPos + 1);

        // Convert minValStr and maxValStr to integers
        int minVal, maxVal;
        try {
            minVal = stoi(minValStr);
            maxVal = stoi(maxValStr);
        } catch (const invalid_argument& e) {
            cerr << ERROR_INVALID_FORMAT << endl;
            continue; // Skip this line and continue with the next one
        }

        // Create a Range struct and store it in the map
        rangeMap[filename_attribute] = {minVal, maxVal};
    }

    rangeFile.close();
    return rangeMap;
}

// Function to update the range output file
void updateRangeOutputFile(const map<string, Range>& rangeMap, const string& filePath, int stateCounter) {
    ofstream rangeOutputFile(filePath, ios::app); // Append to the output file
    if (!rangeOutputFile.is_open()) {
        cerr << ERROR_OPEN_FILE << filePath << endl;

        // Attempt to create the file if it doesn't exist
        rangeOutputFile.open(filePath);
        if (!rangeOutputFile.is_open()) {
            cerr << "Error: Unable to create or open the output file." << endl;
            return;
        }
    }

    // Write the state name (e.g., S0, S1, etc.)
    rangeOutputFile << "S" << stateCounter << endl;

    // Write the updated range values
    for (const auto& entry : rangeMap) {
        rangeOutputFile << entry.first << "[" << entry.second.min_val << "," << entry.second.max_val << "]" << endl;
    }

    rangeOutputFile.close();
}

void processStatements(const string& inputFilePath, const string& rangeInputFilePath, const string& rangeOutputFilePath) {
    map<string, Range> rangeMap = readRangeInputFile(rangeInputFilePath);
 
    ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        cerr << ERROR_OPEN_FILE << inputFilePath << endl;
        return;
    }

    string statement;
    int stateCounter = 0;

    while (getline(inputFile, statement)) {
        // cout<<statement<<endl;
        if (validateStatement(statement)) {
            // Increment the state counter for each valid statement
            stateCounter++;
            if (statement.find("INSERT") != string::npos) {
                 
                 int l_ = statement.size();
                 vector<string>cc;
                 string now = "";
                 bool not_oc = false;
                 string prev = "";
                 for(auto it : statement)
                 {
                      if(it!=' ')now += it; 
                     if(it == ' ')
                     { 
                        
                        if(prev == "INTO" )
                        {
                            break;
                        } 
                        prev = now;
                        now = "";
                     }
                    
                 }
                 string final_num = "";
                 bool ok = false;
                 for(int i = 0 ; i < l_ ; i++)
                 {
                       if(ok && statement[i] != ')' && statement[i] != ';')   final_num += statement[i];
                       if(statement[i] == '(')    ok = true;
                 }
                 int nnum = stoi(final_num);
                    
                    rangeMap[now].min_val = min(rangeMap[now].min_val , nnum);
                    rangeMap[now].max_val = max( rangeMap[now].max_val  , nnum);
   
            } else if (statement.find("UPDATE") != string::npos) {

                 string now = "";
                 string prev = "";
                 for(auto it : statement)
                 {  
                     if(it!=' ')now += it; 
                     if(it == ' ')
                     { 
                        if(prev == "=" ) 
                        {
                            break;
                        }
                        prev = now;
                        now = ""; 
                     }
                 }
               string mystr = now; 
            //    cout<<"now -> "<<now<<endl;
               now = "";
               prev = "";
               bool less = false , grt = false;
               for(auto it : statement)
                 {  
                        if( it == '<' )
                          {
                              less = true;break;
                          }
                          if(it == '>')
                          {
                              grt = true;break;
                          }
                     
                 }

               now = "" ;
               prev = "" ;
               for(auto it : statement)
                 {  
                     if(it!=' ' && it != ';')now += it; 
                     if(it == ' ')
                     { 
                          if(prev == "UPDATE")
                          {
                             break;
                          }
                        prev = now;
                        now = "";
                     }
                 }

                 
                string myattr  = now ;


               now = "" ;
               prev = "" ;
               for(auto it : statement)
                 {  
                     if(it!=' ' && it != ';')now += it; 
                     if(it == ' ')
                     { 
                          if(prev == ">" || prev == "<")
                          {
                             break;
                          }
                        prev = now;
                        now = "";
                     }
                 }
                string _last = now ;

                bool plus = false  , minus = false , mul = false  , div = false , modu  = false ; 
                string mynum = "";
                for(auto it : mystr)
                {
                      if(plus || minus || modu || div ||  mul) mynum += it;
                      if(it == '+')   plus = true;
                      if(it == '-')   minus = true;
                      if(it == '%')   modu = true;
                      if(it == '/')   div = true;
                      if(it == '*')   mul = true;
                }

              if(less)
              {
                    if(plus || minus || modu || div || mul) 
                    {
                         if(rangeMap[myattr].max_val < stoi(_last) )
                         {
                              if(plus)
                              {
                                  rangeMap[myattr].max_val += stoi((mynum));
                                  rangeMap[myattr].min_val += stoi((mynum));
                              }
                              if(minus)
                              {
                                  rangeMap[myattr].max_val -= stoi((mynum));
                                  rangeMap[myattr].min_val -= stoi((mynum));
                                 
                              }
                              if(modu)
                              {
                                  rangeMap[myattr].max_val %= stoi((mynum));
                                  rangeMap[myattr].min_val %= stoi((mynum));
                              }
                              if(div)
                              {
                                    rangeMap[myattr].max_val /= stoi((mynum));
                                    rangeMap[myattr].min_val /= stoi((mynum));
                              }
                             if(mul)
                              {
                                    rangeMap[myattr].max_val *= stoi((mynum));
                                    rangeMap[myattr].min_val *= stoi((mynum));
                                 
                              }
                              

                         }     
                        else if(rangeMap[myattr].min_val < stoi(_last))
                         {
                             if(plus)
                              {
                                  rangeMap[myattr].min_val += stoi((mynum));
                              }
                              if(minus)
                              {
                                  rangeMap[myattr].min_val -= stoi((mynum));
                              }
                              if(modu)
                              {
                                  rangeMap[myattr].min_val %= stoi((mynum));
                              }
                              if(div)
                              {
                                    rangeMap[myattr].min_val /= stoi((mynum));
                              }
                             if(mul)
                              {
                                    rangeMap[myattr].min_val *= stoi((mynum));
                              }
                         }
                    }
                  else if( ( rangeMap[myattr].min_val <= stoi(_last) ) && ( stoi(_last) <= rangeMap[myattr].max_val ) )
                      rangeMap[myattr].min_val =   stoi(mystr) ;
              }
              else
              {
                 if(plus || minus || modu || div || mul) 
                    {
                         if(rangeMap[myattr].min_val > stoi(_last) )
                         {
                              if(plus)
                              {
                                  rangeMap[myattr].max_val += stoi((mynum));
                                  rangeMap[myattr].min_val += stoi((mynum));
                              }
                              if(minus)
                              {
                                  rangeMap[myattr].max_val -= stoi((mynum));
                                  rangeMap[myattr].min_val -= stoi((mynum));
                                 
                              }
                              if(modu)
                              {
                                  rangeMap[myattr].max_val %= stoi((mynum));
                                  rangeMap[myattr].min_val %= stoi((mynum));
                              }
                              if(div)
                              {
                                    rangeMap[myattr].max_val /= stoi((mynum));
                                    rangeMap[myattr].min_val /= stoi((mynum));
                              }
                             if(mul)
                              {
                                    rangeMap[myattr].max_val *= stoi((mynum));
                                    rangeMap[myattr].min_val *= stoi((mynum));
                              }
                         }     
                        else if(rangeMap[myattr].max_val >  stoi(_last))
                         {
                             if(plus)
                              {
                                  rangeMap[myattr].max_val += stoi((mynum));
                              }
                              if(minus)
                              {
                                  rangeMap[myattr].max_val -= stoi((mynum));
                              }
                              if(modu)
                              {
                                  rangeMap[myattr].max_val %= stoi((mynum));
                              }
                              if(div)
                              {
                                    rangeMap[myattr].max_val /= stoi((mynum));
                              }
                             if(mul)
                              {
                                    rangeMap[myattr].max_val *= stoi((mynum));
                              }
                         }
                    }
                 else if( ( rangeMap[myattr].min_val <= stoi(_last) ) && ( stoi(_last) <= rangeMap[myattr].max_val ) )
                  rangeMap[myattr].max_val = stoi(mystr);
              }

            } else if (statement.find("DELETE") != string::npos) {
                   string now = "";
                 string prev = "";
                
               string mystr = now; 
               now = "";
               prev = "";
               bool less = false , grt = false;
               for(auto it : statement)
                 {  
                        if( it == '<' )
                          {
                              less = true;break;
                          }
                          if(it == '>')
                          {
                              grt = true;break;
                          }
                     
                 }

               now = "" ;
               prev = "" ;
               for(auto it : statement)
                 {  
                     if(it!=' ' && it != ';')now += it; 
                     if(it == ' ')
                     { 
                          if(prev == "FROM")
                          {
                             break;
                          }
                        prev = now;
                        now = "";
                     }
                 }

                 
                string myattr  = now ;


               now = "" ;
               prev = "" ;
               for(auto it : statement)
                 {  
                     if(it!=' ' && it != ';')now += it; 
                     if(it == ' ')
                     { 
                          if(prev == ">" || prev == "<")
                          {
                             break;
                          }
                        prev = now;
                        now = "";
                     }
                 }
                string _last = now ;

              if(less)
              {
                    if( ( rangeMap[myattr].min_val <= stoi(_last) ) && ( stoi(_last) <= rangeMap[myattr].max_val ) )
                      rangeMap[myattr].min_val =   stoi(_last) ;
              }
              else
              {
                 if( ( rangeMap[myattr].min_val <= stoi(_last) ) && ( stoi(_last) <= rangeMap[myattr].max_val ) )
                  rangeMap[myattr].max_val = stoi(_last);
              }
            } else if (statement.find("SELECT") != string::npos) {
            } else {
                cerr << WARNING_UNRECOGNIZED_STATEMENT << statement << endl;
            }
            updateRangeOutputFile(rangeMap, rangeOutputFilePath, stateCounter);
        } else {
            cerr << ERROR_INVALID_STATEMENT << statement << endl;
        }
    }

    inputFile.close();
}

int main() {
    //  std::chrono::steady_clock::time_point start_time, end_time;

    // // Record the start time
    // start_time = std::chrono::steady_clock::now();
    // Specify file paths for input and output files
    string inputFilePath = "C:\\Users\\ADMIN\\Desktop\\7th sem\\project\\New folder\\modified_range_input.txt";
    string rangeInputFilePath = "C:\\Users\\ADMIN\\Desktop\\7th sem\\project\\New folder\\modified_range_range.txt";
 
    string rangeOutputFilePath = "output_range.txt";
    ofstream outputFile(rangeOutputFilePath, ios::out | ios::trunc);
    // Process the statements and update the range output file
    processStatements(inputFilePath, rangeInputFilePath, rangeOutputFilePath);
    // Record the end time
    // end_time = std::chrono::steady_clock::now();
    // std::chrono::duration<double> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
    // std::cout << "Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}