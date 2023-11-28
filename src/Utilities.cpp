//
// Created by janek on 25.11.2023.
//

#include "Utilities.h"
#include "CTree.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int Utilities::whichType(const string& statement) {
    if(isNumber(statement))
        return 0;
    if(statement == "+")
        return 2;
    if(statement == "-")
        return 3;
    if(statement == "*")
        return 4;
    if(statement == "/")
        return 5;
    if(statement == "sin")
        return 6;
    if(statement == "cos")
        return 7;
    if(statement == "supersum")
        return 8;
    return 1;

}

int Utilities::convertStringToInt(const string &str) {
    int result;
    stringstream convert(str);
    if ( !(convert >> result) )
        result = 0;
    return result;
}

bool Utilities::isNumber(const string& s) {
    if (s.empty()) return false;

    for (size_t i = 0; i < s.length(); ++i) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

vector<string> Utilities::convertToVector(string expression) {
    vector<string> table;
    size_t iterator = 0;
    while (iterator < expression.size()) {
        string part;
        while (iterator < expression.size() && expression[iterator] != ' ')
            part += expression[iterator++];

        iterator++;
        if (!part.empty())
            table.push_back(part);
    }
    return table;
}

void Utilities::initialize() {
    CTree cTree;
    string command;
    while (command != "exit") {
        cout << "Podaj polecenie -> ";
        string expression;
        getline(cin, expression);

        vector<string> line = convertToVector(expression);

        command= line[0];
        line.erase(line.begin());

        if(command != "exit")
            cTree = executeOperation(command, line, cTree);
    }
}

vector<int> Utilities::convertVectorStringToInt(vector<string> &variables) {
    vector<int> result;
    result.reserve(variables.size());
    for (int i = 0; i < variables.size(); ++i)
        result.push_back(convertStringToInt(variables[i]));

    return result;
}

CTree Utilities::executeOperation(string &command, vector<string> &line, CTree &cTree) {
    if (command == "enter") {
        CTree newCTree(line);
        cout << "Wczytane polecenie: ";
        newCTree.prefixTraverse();
        return newCTree;
    } else if (command == "print")
        cTree.prefixTraverse();
    else if (command == "comp")
        cout << cTree.compute(convertVectorStringToInt(line)) << endl;
    else if (command == "join") {
        cTree = cTree + CTree(line);
        cTree.prefixTraverse();
    } else if (command == "vars"){
        vector<string> variables = CTree::findVariables(cTree.getRoot());
        for (int i = 0; i < variables.size(); ++i)
            cout << variables[i] << " ";
        cout << endl;
    }
    else
        cout << "Niepoprawna komenda" << endl;
    return cTree;

}