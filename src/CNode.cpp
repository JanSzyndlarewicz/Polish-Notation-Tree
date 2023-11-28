//
// Created by janek on 26.11.2023.
//

#include "CNode.h"
//
// Created by janek on 25.11.2023.
//

#include "CNode.h"
#include "Utilities.h"

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

CNode::CNode() {
    value = -1;
    type = 0;
}

CNode::CNode(int value) : children() {
    this->value = value;
    type = 0;
}

CNode::CNode(const string &statement) : value(), children() {
    type = Utilities::whichType(statement);
    if (type == 0)
        this->value = Utilities::convertStringToInt(statement);
    else
        this->operationOrVariable = statement;


}

CNode::CNode(const vector<string> &exp, int *index) {
    (*index)++;
    type = Utilities::whichType(exp[*index]);
    this->operationOrVariable = exp[*index];
    if (type == 0)
        this->value = Utilities::convertStringToInt(exp[*index]);
    else if(type == 8){
        children.push_back(CNode(exp, index));
        children.push_back(CNode(exp, index));
        children.push_back(CNode(exp, index));
        children.push_back(CNode(exp, index));
    }
    else if (type > 5)
        children.push_back(CNode(exp, index));
    else if (type > 1) {
        children.push_back(CNode(exp, index));
        children.push_back(CNode(exp, index));
    }
}

double CNode::compute(vector<string> variables, vector<int> &values) {
    switch (type) {
        case 0:
            return value;
        case 1:
            return values[find(variables.begin(), variables.end(), operationOrVariable) - variables.begin()];
        case 2:
            return children[0].compute(variables, values) + children[1].compute(variables, values);
        case 3:
            return children[0].compute(variables, values) - children[1].compute(variables, values);
        case 4:
            return children[0].compute(variables, values) * children[1].compute(variables, values);
        case 5:
            return children[0].compute(variables, values) / children[1].compute(variables, values);
        case 6:
            return sin(children[0].compute(variables, values));
        case 7:
            return cos(children[0].compute(variables, values));
        case 8:
            return children[0].compute(variables, values) + children[1].compute(variables, values) + children[2].compute(variables, values) + children[3].compute(variables, values);
    }

    return 0;
}

void CNode::printPreorderTraverse() {
    cout<<toString()<< " ";
    for (CNode child:getChildren())
        child.printPreorderTraverse();
}

CNode* CNode::getLeftLeaf() {
    if(children.empty())
        return this;
    return children[0].getLeftLeaf();
}


string CNode::toString() const {
    if (type == 0) {
        stringstream valueToStr;
        valueToStr << value;
        return valueToStr.str();
    }

    return operationOrVariable;
}

int CNode::getType() const {
    return type;
}

int CNode::getValue() const {
    return value;
}

string CNode::getOperationOrVariable() const {
    return operationOrVariable;
}

vector<CNode> &CNode::getChildren() {
    return children;
}

void CNode::setValue(int val) {
    CNode::value = val;
}

void CNode::setOperationOrVariable(const string &opOrVar) {
    operationOrVariable = opOrVar;
}

void CNode::setChildren(const vector<CNode> &childrenVector) {
    CNode::children = childrenVector;
}

bool CNode::isVariable() {
    return type == 1;
}