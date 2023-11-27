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

CTree::CTree(const vector<string> &expression) {
    int *index = new int(-1);
    root = CNode(expression, index);
    if (*index < expression.size() - 1)
        cout << "Podane za duzo elementow. ";
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
    *root.getLeftLeaf() = tree.root;
    return *this;
}
