//
// Created by janek on 26.11.2023.
//

#ifndef UNTITLED_CNODE_H
#define UNTITLED_CNODE_H


#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "Utilities.h"


using namespace std;

template <typename T> class CNode {
private:
    int type;
    T value;
    string operationOrVariable;
    vector< CNode<T> > children;

public:
    CNode();
    explicit CNode(int value);
    explicit CNode(const string& statement);
    explicit CNode(vector<string> &exp, int *index);


    T compute(vector<string> variables, vector<T> values);
    void printPreorderTraverse();
    string toString() const;

    int getType() const;
    T getValue() const;
    string getOperationOrVariable() const;
    vector<CNode> &getChildren();
    void setValue(int val);
    void setOperationOrVariable(const string &opOrVar);
    void setChildren(const vector<CNode>& childrenVector);


    bool isVariable();

    CNode *getLeftLeaf();


    int whichType(const string &statement);

    bool isNumber(const string &s);

    int stringToInt(const string &str);

    double stringToDouble(string &str);

    int whichTypeDouble(const string &statement);

    bool isDouble(const string &s);
};

template <typename T>
CNode<T>::CNode() {
    value = -1;
    type = 0;
}

template <typename T>
CNode<T>::CNode(int value) : children() {
    this->value = value;
    type = 0;
}

template <typename T>
CNode<T>::CNode(const string &statement) : value(), children() {
    type = whichType(statement);
    if (type == 0)
        this->value = stringToInt(statement);
    else {
        this->operationOrVariable = statement;
    }

}

template <>
CNode<int>::CNode(vector<string> &exp, int *index) {
    (*index)++;
    type = whichType(exp[*index]);
    this->operationOrVariable = exp[*index];
    if (type == 0)
        this->value = stringToInt(exp[*index]);
    else if (type > 5)
        children.push_back(CNode(exp, index));
    else if (type > 1) {
        children.push_back(CNode(exp, index));
        children.push_back(CNode(exp, index));
    }
}

template <>
CNode<double>::CNode(vector<string> &exp, int *index) {
    (*index)++;
    type = whichTypeDouble(exp[*index]);
    this->operationOrVariable = exp[*index];
    if (type == 0)
        this->value = stringToDouble(exp[*index]);
    else if (type > 5)
        children.push_back(CNode(exp, index));
    else if (type > 1) {
        children.push_back(CNode(exp, index));
        children.push_back(CNode(exp, index));
    }
}

template <typename T>
CNode<T>::CNode(vector<string> &exp, int *index) {
    (*index)++;
    type = whichType(exp[*index]);
    this->operationOrVariable = exp[*index];
    if (type == 0)
        this->value = stringToInt(exp[*index]);
    else if (type > 5)
        children.push_back(CNode(exp, index));
    else if (type > 1) {
        children.push_back(CNode(exp, index));
        children.push_back(CNode(exp, index));
    }
}

template<typename T>
double CNode<T>::stringToDouble(string &str) {
    stringstream ss(str);
    double ld;
    if(!(ss >> ld))
        ld = 0;
    cout << ld << endl;
    return ld;
}

template <typename T>
int CNode<T>::whichType(const string& statement) {
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

template <typename T>
int CNode<T>::whichTypeDouble(const string& statement) {
    if(isDouble(statement))
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

template <typename T>
bool CNode<T>::isDouble(const string& s) {
    if (s.empty()) return false;

    for (size_t i = 0; i < s.length(); ++i) {
        if (!isdigit(s[i]) && s[i] != '.') {
            return false;
        }
    }
    return true;
}


template <typename T>
bool CNode<T>::isNumber(const string& s) {
    if (s.empty()) return false;

    for (size_t i = 0; i < s.length(); ++i) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

template <typename T>
int CNode<T>::stringToInt(const string &str) {
    int result;
    stringstream convert(str);
    if ( !(convert >> result) )
        result = 0;
    return result;
}


template <>
int CNode<int>::compute(vector<string> variables, vector<int> values) {

    switch (type) {
        case 0:
            return value;
        case 1: {
            int index = find(variables.begin(), variables.end(), operationOrVariable) - variables.begin();
            return values[index];
        }
        case 2:
            return children[0].compute(variables, values) + children[1].compute(variables, values);
        case 3:
            return children[0].compute(variables, values) - children[1].compute(variables, values);
        case 4:
            return children[0].compute(variables, values) * children[1].compute(variables, values);
        case 5:
            return children[0].compute(variables, values) / children[1].compute(variables, values);
    }

    return 0;
}

template <>
double CNode<double>::compute(vector<string> variables, vector<double> values) {

    switch (type) {
        case 0:
            return value;
        case 1: {
            int index = find(variables.begin(), variables.end(), operationOrVariable) - variables.begin();
            return values[index];
        }
        case 2:
            return children[0].compute(variables, values) + children[1].compute(variables, values);
        case 3:
            return children[0].compute(variables, values) - children[1].compute(variables, values);
        case 4:
            return children[0].compute(variables, values) * children[1].compute(variables, values);
        case 5:
            return children[0].compute(variables, values) / children[1].compute(variables, values);
    }

    return 0;
}

template <typename T>
T CNode<T>::compute(vector<string> variables, vector<T> values) {
    switch (type) {
        case 0:
            return value;
        case 1: {
            int index = find(variables.begin(), variables.end(), operationOrVariable) - variables.begin();
            return values[index];
        }
        case 2:
            return children[0].compute(variables, values) + children[1].compute(variables, values);
//        case 3:
//            return Utilities::subtractStrings(children[0].compute(variables, values), children[1].compute(variables, values));
            //return children[0].compute(variables, values) - children[1].compute(variables, values);
//        case 4:
//            return children[0].compute(variables, values) * children[1].compute(variables, values);
//        case 5:
//            return children[0].compute(variables, values) / children[1].compute(variables, values);
    }

    return 0;
}

template <typename T>
void CNode<T>::printPreorderTraverse() {
    cout<<toString()<< " ";
    for (CNode child:getChildren())
        child.printPreorderTraverse();
}

template <typename T>
CNode<T>* CNode<T>::getLeftLeaf() {
    if(children.empty())
        return this;
    return children[0].getLeftLeaf();
}

template <typename T>
string CNode<T>::toString() const {
    if (type == 0) {
        stringstream valueToStr;
        valueToStr << value;
        return valueToStr.str();
    }

    return operationOrVariable;
}

template <typename T>
int CNode<T>::getType() const {
    return type;
}

template <typename T>
T CNode<T>::getValue() const {
    return value;
}

template <typename T>
string CNode<T>::getOperationOrVariable() const {
    return operationOrVariable;
}

template <typename T>
vector<CNode<T> > &CNode<T>::getChildren() {
    return children;
}

template <typename T>
void CNode<T>::setValue(int val) {
    CNode::value = val;
}

template <typename T>
void CNode<T>::setOperationOrVariable(const string &opOrVar) {
    operationOrVariable = opOrVar;
}

template <typename T>
void CNode<T>::setChildren(const vector<CNode> &childrenVector) {
    CNode::children = childrenVector;
}

template <typename T>
bool CNode<T>::isVariable() {
    return type == 1;
}

#endif //UNTITLED_CNODE_H
