#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
vector<string> split(string input, string splitter){
    vector<string> ret = vector<string>();
    string inputc = input;
    while(inputc.size() > 0){
        string val = ""; 
        if (inputc.find(splitter) == string::npos){
            val = inputc;
            break;
        }else{
            val = inputc.substr(0,inputc.find(splitter));
            inputc.erase(0,inputc.find(splitter));
        }
        ret.push_back(val);
    }
    return ret;
}
vector<int> splitint(string input, string splitter){
    vector<int> ret = vector<int>();
    string inputc = input;
    while(inputc.size() > 0){
        int val = 0; 
        if (inputc.find(splitter) == string::npos){
            val = atoi(inputc.c_str());
            
        }else{
            val = atoi(inputc.substr(0,inputc.find(splitter)).c_str());
            inputc.erase(0,inputc.find(splitter));
        }
        ret.push_back(val);
        
    }
    return ret;
}