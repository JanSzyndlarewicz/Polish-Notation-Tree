//
// Created by janek on 26.11.2023.
//

#ifndef UNTITLED_CTREE_H
#define UNTITLED_CTREE_H


#include "CNode.h"
#include <string>
#include <vector>
#include <iostream>

class CTree {
private:
    CNode root;

public:
    CTree();

    explicit CTree(const vector<string>& expression);
    static vector<string> findVariables(CNode &node);
    void prefixTraverse();
    double compute(vector<int> values);
    CNode &getRoot();
    CTree operator+(const CTree &tree);
};


#endif //UNTITLED_CTREE_H
