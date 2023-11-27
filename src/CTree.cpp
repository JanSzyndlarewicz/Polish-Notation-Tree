//
// Created by janek on 26.11.2023.
//

#include "CTree.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void CTree::prefixTraverse() {
    root.printPreorderTraverse();
    cout << endl;
}
vector<string> CTree::findVariables(CNode &node) {
    vector<string> variables;
    if (node.isVariable()) {
        if(variables.end() == find(variables.begin(), variables.end(), node.toString()))
            variables.push_back(node.toString());
    } else {
        for (CNode child:node.getChildren())
            for (string variable:findVariables(child))
                if(variables.end() == find(variables.begin(), variables.end(), variable))
                    variables.push_back(variable);
    }

    return variables;
}

CTree::CTree(const vector<string>& expression) {
    int *index = new int(-1);
    root = CNode(expression, index);
    delete index;
}

CTree::CTree() {}

double CTree::compute(vector<int> values) {
    return root.compute(findVariables(root), values);
}

CNode &CTree::getRoot() {
    return root;
}

CTree CTree::operator+(const CTree &tree) {
    *root.getLeftLeaf()=tree.root;
    return *this;
}
