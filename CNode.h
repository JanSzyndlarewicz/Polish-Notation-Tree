//
// Created by janek on 26.11.2023.
//

#ifndef UNTITLED_CNODE_H
#define UNTITLED_CNODE_H


#include <string>
#include <vector>

using namespace std;

class CNode {
private:
    int type;
    int value;
    string operationOrVariable;
    vector<CNode> children;

public:
    CNode();
    explicit CNode(int value);
    explicit CNode(const string& statement);
    explicit CNode(const vector<string> &exp, int *index);

    void addChild(CNode& child);
    double compute(vector<string> variables, vector<int> &values);
    void findAllVariables(vector<string> &variables);
    void printPreorderTraverse();
    string toString() const;
    int getType() const;
    int getValue() const;
    string getOperationOrVariable() const;
    vector<CNode> &getChildren();
    void setValue(int val);
    void setOperationOrVariable(const string &opOrVar);
    void setChildren(const vector<CNode>& childrenVector);


    bool isVariable();

    CNode *getLeaf();
};


#endif //UNTITLED_CNODE_H
