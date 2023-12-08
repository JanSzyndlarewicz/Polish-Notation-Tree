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
    static int stringToInt(const string &str);

    static bool isNumber(const string& s);

    static int whichType(const string& statement);

    static vector<string> convertToVector(string expression);

    void initialize();
    static vector<int> convertToInt(vector<string> &variables);
    static string subtractStrings(basic_string<char> s1, basic_string<char> s2);

    template<typename T>
    CTree<T> executeOperation(string &command, vector<string> &line, CTree<T> &cTree);

    template<typename T>
    void bridgeLoop(CTree<T> &cTree);

};


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
    return 1;

}

int Utilities::stringToInt(const string &str) {
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
    while (true) {
        cout << "Wybierz typ drzewa:" << endl;
        cout << "1. String" << endl;
        cout << "2. Double" << endl;
        cout << "3. Int" << endl;
        cout << "4. Exit" << endl;
        string type;
        cin >> type;
        if (type == "1") {
            CTree<string> tree;
            bridgeLoop(tree);
        } else if (type == "2") {
            CTree<double> tree;
            bridgeLoop(tree);
        } else if (type == "3") {
            CTree<int> tree;
            bridgeLoop(tree);
        } else if (type == "4") {
            return;
        } else {
            cout << "Niepoprawny wybór" << endl;

        }
    }
}

template<typename T>
void Utilities::bridgeLoop(CTree<T> &cTree){
    string command;
    while (command != "exit") {
        cout << "Podaj polecenie -> " << endl;
        string expression;

        while(expression.empty())
            getline(cin, expression);

        vector<string> line = convertToVector(expression);

        command = line[0];

        line.erase(line.begin());

        if(command != "exit")
            cTree = executeOperation(command, line, cTree);
    }
}

vector<int> Utilities::convertToInt(vector<string> &variables) {
    vector<int> result;
    result.reserve(variables.size());
    for (int i = 0; i < variables.size(); ++i) {
        result.push_back(stringToInt(variables[i]));
    }
    return result;
}


template<typename T>
CTree<T> Utilities::executeOperation(string &command, vector<string> &line, CTree<T> &cTree) {
    vector<string> x;
    if (command == "enter") {
        CTree<T> newCTree(line);
        cout << "Wczytane polecenie: ";
        newCTree.prefixTraverse();
        return newCTree;
    } else if (command == "print")
        cTree.prefixTraverse();
    else if (command == "comp")
        cout << cTree.compute(line) << endl;
//    else if (command == "join") {
//        cTree = cTree + CTree<string>(line);
//        cTree.prefixTraverse();
    //}
    else if (command == "vars"){
        vector<string> variables = CTree<T>::findVariables(cTree.getRoot());
        for (int i = 0; i < variables.size(); ++i)
            cout << variables[i] << " ";
        cout << endl;
    }
    else
        cout << "Niepoprawna komenda" << endl;
    return cTree;

}

string Utilities::subtractStrings(basic_string<char> s1, basic_string<char> s2) {
    if(s1.find(s2) == string::npos)
        return s1;
    s1.erase(s1.rfind(s2), s2.length());
    return s1;
}



#endif //UNTITLED_UTILITIES_H
