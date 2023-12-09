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

    T stringToT(string &str);
    int whichTypeOfT(const string &statement);
    bool isValue(const string &s);

    string subtract(string string1, string string2);

    string multiply(string string1, string string2);

    string divider(string string1, const string& string2);
};

template<typename T>
string CNode<T>::divider(string string1, const string& string2) {
    while(string1.find(string2) != string::npos)
        string1.erase(string1.find(string2)+1, string2.length()-1);
    return string1;
}

template<typename T>
string CNode<T>::multiply(string string1, string string2) {
    string result;
    for(int i = 0; i < string1.length(); ++i) {
        if(string1[i]==string2[0])
            result+=string2;
        else{
            result+=string1[i];
        }
    }
    return result;
}

template<typename T>
string CNode<T>::subtract(string string1, string string2) {
    if(string1.find(string2) == string::npos)
        return string1;
    string1.erase(string1.rfind(string2), string2.length());
    return string1;
}

template<typename T>
bool CNode<T>::isValue(const string &s) {
    return false;
}

template<>
bool CNode<string>::isValue(const string &s) {
    if (s.empty())
        return false;

    if(s[0] != '"' || s[s.length() - 1] != '"')
        return false;

    return true;
}

template<>
bool CNode<double>::isValue(const string &s) {
    if (s.empty())
        return false;

    for (size_t i = 0; i < s.length(); ++i)
        if (!isdigit(s[i]) && s[i] != '.')
            return false;

    return true;
}

template<>
bool CNode<int>::isValue(const string &s) {
    if (s.empty())
        return false;

    for (size_t i = 0; i < s.length(); ++i)
        if (!isdigit(s[i]))
            return false;

    return true;
}

template<typename T>
int CNode<T>::whichTypeOfT(const string &statement) {
    if(isValue(statement))
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

template<typename T>
T CNode<T>::stringToT(string &str) {
    cout << "This should never happen" << endl;
    T result;
    return result;
}

template<>
string CNode<string>::stringToT(string &str) {
    str.erase(remove(str.begin(), str.end(), '"'), str.end());
    return str;
}

template<>
int CNode<int>::stringToT(string &str) {
    int result;
    stringstream convert(str);
    if (!(convert >> result))
        result = 0;
    return result;
}

template<>
double CNode<double>::stringToT(string &str) {
    double result;
    stringstream convert(str);
    if (!(convert >> result))
        result = 0;
    return result;
}

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
    type = whichTypeOfT(statement);
    if (type == 0)
        this->value = stringToT(statement);
    else {
        this->operationOrVariable = statement;
    }

}

template <typename T>
CNode<T>::CNode(vector<string> &exp, int *index) {
    (*index)++;
    type = whichTypeOfT(exp[*index]);
    this->operationOrVariable = exp[*index];
    if (type == 0)
        this->value = stringToT(exp[*index]);
    else if (type > 5)
        children.push_back(CNode(exp, index));
    else if (type > 1) {
        children.push_back(CNode(exp, index));
        children.push_back(CNode(exp, index));
    }
}

template <>
string CNode<string>::compute(vector<string> variables, vector<string> values) {
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
            return subtract(children[0].compute(variables, values), children[1].compute(variables, values));
        case 4:
            return multiply(children[0].compute(variables, values), children[1].compute(variables, values));
        case 5:
            return divider(children[0].compute(variables, values), children[1].compute(variables, values));;
    }

    return "";
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
