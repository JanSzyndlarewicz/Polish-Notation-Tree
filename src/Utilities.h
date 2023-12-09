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
    static vector<string> convertToVector(string expression);
    void initialize();
    template<typename T> CTree<T> executeOperation(string &command, vector<string> &line, CTree<T> &cTree);
    template<typename T> void bridgeLoop(CTree<T> &cTree);
};

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
        } else if (type == "4")
            return;
        else
            cout << "Niepoprawny wybór" << endl;
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

template<typename T>
CTree<T> Utilities::executeOperation(string &command, vector<string> &line, CTree<T> &cTree) {
    if (command == "enter") {
        CTree<T> newCTree(line);
        cout << "Wczytane polecenie: ";
        newCTree.prefixTraverse();
        return newCTree;
    } else if (command == "print")
        cTree.prefixTraverse();
    else if (command == "comp")
        cout << cTree.compute(line) << endl;
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



#endif //UNTITLED_UTILITIES_H
