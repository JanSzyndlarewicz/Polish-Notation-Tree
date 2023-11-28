//
// Created by janek on 26.11.2023.
//

#ifndef UNTITLED_UTILITIES_H
#define UNTITLED_UTILITIES_H


#include <string>
#include <vector>
#include "CTree.h"

using namespace std;

class Utilities {
public:
    static int convertStringToInt(const string &str);
    static bool isNumber(const string& s);
    static int whichType(const string& statement);
    static vector<string> convertToVector(string expression);
    static void initialize();
    static CTree executeOperation(string &command, vector<string> &line, CTree &cTree);
    static vector<int> convertVectorStringToInt(vector<string> &variables);
};


#endif //UNTITLED_UTILITIES_H
