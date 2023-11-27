#include <bits/stdc++.h>
using namespace std;

// Structure to represent a policy condition
struct PolicyCondition {
    string attribute1;
    string op1;
    int val1;
    string attribute2;
    string op2;
    int val2;
};

// Structure to represent a state
struct State {
    string name;
    vector<pair<string, pair<int, int>>> attributes;
};

// Function to parse a policy condition from a string
PolicyCondition parsePolicyCondition(const string& conditionStr) {
    PolicyCondition condition;
    stringstream ss(conditionStr);
    ss >> condition.attribute1 >> condition.op1 >> condition.val1 
       >> condition.attribute2 >> condition.op2 >> condition.val2;
    return condition;
}

// Function to parse a state from a string
State parseState(const string& stateStr) {
    State state;
    stringstream ss(stateStr);
    ss >> state.name;
    string attrName;
    pair<int, int> attrRange;
    while (ss >> attrName >> attrRange.first >> attrRange.second) {
        state.attributes.push_back({attrName, attrRange});
    }
    return state;
}

bool isPolicySatisfied(const PolicyCondition& policy, const State& state) {

    for (const auto& attr : state.attributes) {
        if (attr.first == policy.attribute1) {
            if ((policy.op1 == ">=" && attr.second.second >= policy.val1) ||
                (policy.op1 == "<=" && attr.second.first <= policy.val1)) {
                continue;
            } else {
                return false;
            }
        }
        if (attr.first == policy.attribute2) {
            if ((policy.op2 == ">=" && attr.second.second >= policy.val2) ||
                (policy.op2 == "<=" && attr.second.first <= policy.val2)) {
                continue;
            } else {
                return false;
            }
        }
    }
  
    return true; 
}

// Function to read and process policy and range files
void processFiles(const string& policyFilePath, const string& rangeFilePath) {
    ifstream policyFile(policyFilePath);
    ifstream rangeFile(rangeFilePath);

    vector<PolicyCondition> policies;
    vector<State> states;

    // Parse the policies
    string line;
    while (getline(policyFile, line)) {
        policies.push_back(parsePolicyCondition(line));
    }
    cout<<line<<endl;
    // Parse the states
    while (getline(rangeFile, line)) {
        states.push_back(parseState(line));
    }
    string ch1 , ch2;
    for(auto it  : policies)
    {
        ch1 = it.attribute1;

        ch2 = it.op1;
    }
    pair<int , int>cc1 , cc2;
    bool gr = false , less = false , eq = false;
    string num1  = "",  num2  = "";
    string k1 = "" , k2 = "";
    for(auto it : ch1)
    {
         if(eq)
          {
                num1 += it;
          }
           if(it == '>')
           {
             gr = true;
           }
          if(it == '<')
          {
              less = true;
          }
          if(it == '=')
          {
             eq = true;
          }
         if(!gr && !less)
         {
              k1 += it;
         }
    }

    if(gr)
    {
        cc1 = {stoi(num1) , INT_MAX}; 
    }
    if(less)
    {
        cc1 = {0 , stoi(num1) }; 
    }
    gr = false , less = false , eq = false;
   
    for(auto it : ch2)
    {
         if(eq)
          {
                num2 += it;
          }
          if(it == '>')
           {
             gr = true;
           }
          if(it == '<')
          {
              less = true;
          }
          if(it == '=')
          {
             eq = true;
          }
         if(!gr && !less && it != ',')
         {
              k2 += it;
         }
    }
    // cout<<k2<<endl;// for attribute names
     if(gr)
    {
        cc2 = {stoi(num2) , INT_MAX}; 
    }
    if(less)
    {
        cc2 = {0 , stoi(num2) }; 
    }

    gr = false , less = false , eq = false;
    // Check each state against each policy
      vector<pair<int , int>>v1 , v2;
      for (const auto& it : states) {
       
        string cur = "";
        string num1 = "" , num2 = "";
        bool t1  =  false , t2 = false;
        int tt = 0 ; 
        for(auto it : it.name)
        {
             if(tt)
             {
                        if(it == ']')break;
                        if(t2)
                        num2 += it;
                        if(it == ',')
                        {
                            t2 = true; 
                            t1 = false;
                        }
                        if(t1)
                        num1 += it;
                        if(it == '[')
                        {
                            t1 = true;
                        }
             }
             tt++;
              if(!t1 && !t2)
               cur+=it;
        }
        if(cur == k1)
        {
             v1.push_back({stoi(num1) , stoi(num2)});
        }
        if(cur == k2)
        {
             v2.push_back({stoi(num1), stoi(num2)});
        }
     }


    bool firr = true , secc = true;
    int ind = 0 ; 
    for(auto it : v1)
    {
          firr &=  (cc1.first<= it.first && it.second <= cc1.second) ;
          
    }
    for(auto it : v2)
    {
           secc &=(cc2.first<= it.first && it.second <= cc2.second) ;
    }
   
    if(firr && secc)
    {
        cout<<"SAT"<<endl;
    }
    else{
         cout<<"UNSAT"<<endl;
    }
}

int main() {
    // Specify the output file path
    string outputFilePath = "C:\\Users\\ADMIN\\Desktop\\7th sem\\project\\New folder\\output.txt";

    // Open the output file in truncation mode (overwrite existing content)
    ofstream outputFile(outputFilePath, ios::out | ios::trunc);

    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        cout << "Error opening the output file." << endl;
        return 1;
    }

    // Redirect cout to the output file
    streambuf* coutBuf = cout.rdbuf();
    cout.rdbuf(outputFile.rdbuf());

    // Call the processFiles function
    processFiles("C:\\Users\\ADMIN\\Desktop\\7th sem\\project\\New folder\\excondition.txt",
                 "C:\\Users\\ADMIN\\Desktop\\7th sem\\project\\New folder\\examplerange.txt");

    // Close the output file and restore cout
    outputFile.close();
    cout.rdbuf(coutBuf);

    return 0;
}

