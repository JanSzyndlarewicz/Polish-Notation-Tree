//
// Created by janek on 26.11.2023.
//

#ifndef UNTITLED_CTREE_H
#define UNTITLED_CTREE_H


#include "CNode.h"
#include <string>
#include <vector>
#include <iostream>
template <typename T>
class CTree {
private:
    CNode<T> root;

public:
    CTree();
    explicit CTree(vector<string>& expression);

    static vector<string> findVariables(CNode<T> &node);
    void prefixTraverse();
    T compute(vector<string> &values);
    CNode<T> &getRoot();
    vector<T> convertToT(vector<string> &values);

    CTree operator+(const CTree &tree);


    static int stringToInt(string &str);

    static double stringToDouble(string &str);

    string stringToString(string &str);
};

template<>
vector<int> CTree<int>::convertToT(vector<string> &values) {
    vector<int> result;
    result.reserve(values.size());
    for (int i = 0; i < values.size(); ++i) {
        result.push_back(stringToInt(values[i]));
    }
    return result;
}

template<>
vector<double> CTree<double>::convertToT(vector<string> &values) {
    vector<double> result;
    result.reserve(values.size());

    for (int i = 0; i < values.size(); ++i) {
        result.push_back(stringToDouble(values[i]));
    }

    return result;
}

template<>
vector<string> CTree<string>::convertToT(vector<string> &values) {
    vector<string> result;
    result.reserve(values.size());
    for (int i = 0; i < values.size(); ++i) {
        result.push_back(stringToString(values[i]));
    }
    return result;
}

template<typename T>
vector<T> CTree<T>::convertToT(vector<string> &values) {
    vector<T> result;

    return result;
}


template<typename T>
double CTree<T>::stringToDouble(string &str) {
    stringstream ss(str);
    double ld;
    if(!(ss >> ld))
        ld = 0;
    cout << ld << endl;
    return ld;
}

template<typename T>
int CTree<T>::stringToInt(string &str) {
    int result;
    stringstream convert(str);
    if ( !(convert >> result) )
        result = 0;
    return result;
}

template<typename T>
string CTree<T>::stringToString(string &str) {
    str.erase(remove(str.begin(), str.end(), '"'), str.end());
    return str;
}


template<typename T>
void CTree<T>::prefixTraverse() {
    root.printPreorderTraverse();
    cout << endl;
}

template<typename T>
vector<string> CTree<T>::findVariables(CNode<T> &node) {
    vector<string> variables;
    if (node.isVariable()) {
        if (variables.end() == find(variables.begin(), variables.end(), node.toString()))
            variables.push_back(node.toString());
    } else {
        for (int i = 0; i < node.getChildren().size(); i++)
            for (int j = 0; j < findVariables(node.getChildren()[i]).size(); j++)
                if (variables.end() ==
                    find(variables.begin(), variables.end(), findVariables(node.getChildren()[i])[j]))
                    variables.push_back(findVariables(node.getChildren()[i])[j]);
    }

    return variables;
}

template<typename T>
CTree<T>::CTree(vector<string> &expression) {
    int *index = new int(-1);
    root = CNode<T>(expression, index);
    if (*index < expression.size() - 1)
        cout << "Podane za duzo elementow. ";
    delete index;
}

template<typename T>
CTree<T>::CTree() {}

template<typename T>
T CTree<T>::compute(vector<string> &values) {
    vector<T> tmp = convertToT(values);
    return root.compute(findVariables(root), tmp);
}

template<typename T>
CNode<T> &CTree<T>::getRoot() {
    return root;
}

template<typename T>
CTree<T> CTree<T>::operator+(const CTree<T> &tree) {
    *root.getLeftLeaf() = tree.root;
    return *this;
}

#endif //UNTITLED_CTREE_H
