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

//Konwersja vectora stringów na typ int
template<>
vector<int> CTree<int>::convertToT(vector<string> &values) {
    vector<int> result;
    result.reserve(values.size());
    for (int i = 0; i < values.size(); ++i) {
        result.push_back(stringToInt(values[i]));
    }
    return result;
}

//Konwersja vectora stringów na typ double
template<>
vector<double> CTree<double>::convertToT(vector<string> &values) {
    vector<double> result;
    result.reserve(values.size());

    for (int i = 0; i < values.size(); ++i) {
        result.push_back(stringToDouble(values[i]));
    }

    return result;
}

//Konwersja vectora stringów na typ string
template<>
vector<string> CTree<string>::convertToT(vector<string> &values) {
    vector<string> result;
    result.reserve(values.size());
    for (int i = 0; i < values.size(); ++i) {
        result.push_back(stringToString(values[i]));
    }
    return result;
}


//Konwersja stringów na typ Double
template<typename T>
double CTree<T>::stringToDouble(string &str) {
    stringstream ss(str);
    double ld;
    if(!(ss >> ld))
        ld = 0;
    cout << ld << endl;
    return ld;
}

//Konwersja stringów na typ Int
template<typename T>
int CTree<T>::stringToInt(string &str) {
    int result;
    stringstream convert(str);
    if ( !(convert >> result) )
        result = 0;
    return result;
}

//Konwersja stringów na typ String
template<typename T>
string CTree<T>::stringToString(string &str) {
    str.erase(remove(str.begin(), str.end(), '"'), str.end());
    return str;
}

//Wyświetlanie drzewa w porządku prefiksowym
template<typename T>
void CTree<T>::prefixTraverse() {
    root.printPreorderTraverse();
    cout << endl;
}

//Wyszukiwanie wszystkich zmiennych w drzewie
template<typename T>
vector<string> CTree<T>::findVariables(CNode<T> &node) {
    vector<string> variables; // Inicjacja wektora przechowującego znalezione zmienne

    // Sprawdzenie czy aktualny węzeł jest zmienną
    if (node.isVariable()) {
        // Jeśli jest zmienną i nie została dodana wcześniej do wektora 'variables'
        if (variables.end() == find(variables.begin(), variables.end(), node.toString()))
            variables.push_back(node.toString()); // Dodanie zmiennej do wektora 'variables'
    } else {
        // Jeśli aktualny węzeł nie jest zmienną, iteracja przez wszystkie jego dzieci
        for (int i = 0; i < node.getChildren().size(); i++) {
            // Rekurencyjne wywołanie 'findVariables' dla każdego dziecka
            for (int j = 0; j < findVariables(node.getChildren()[i]).size(); j++) {
                // Sprawdzenie czy zmienna z dziecka nie znajduje się już w 'variables'
                if (variables.end() == find(variables.begin(), variables.end(), findVariables(node.getChildren()[i])[j]))
                    variables.push_back(findVariables(node.getChildren()[i])[j]); // Dodanie zmiennej do 'variables'
            }
        }
    }

    return variables; // Zwrócenie wektora 'variables' zawierającego wszystkie unikalne zmienne w drzewie
}


template<typename T>
CTree<T>::CTree(vector<string> &expression) {
    int *index = new int(-1); // Tworzenie wskaźnika do inta ustawionego na -1
    root = CNode<T>(expression, index); // Inicjacja korzenia drzewa na podstawie wyrażenia i indeksu

    // Sprawdzenie czy podano za dużo elementów do inicjalizacji drzewa
    if (*index < expression.size() - 1)
        cout << "Podane za duzo elementow. "; // Wyświetlenie komunikatu o zbyt dużej liczbie elementów

    delete index; // Zwolnienie zaalokowanej pamięci dla wskaźnika int
}


template<typename T>
CTree<T>::CTree() {}

template<typename T>
T CTree<T>::compute(vector<string> &values) {
    // Konwertowanie wektora stringów na wektor wartości typu T
    vector<T> tmp = convertToT(values);

    // Obliczenie wartości wyrażenia na podstawie wartości zmiennych i drzewa
    return root.compute(findVariables(root), tmp);
}


template<typename T>
CNode<T> &CTree<T>::getRoot() {
    return root;
}

template<typename T>
CTree<T> CTree<T>::operator+(const CTree<T> &tree) {
    CTree<T> result = CTree<T>(*this); // Tworzy kopię bieżącego drzewa

    // Ustawia lewe dziecko liścia lewego poddrzewa wyniku na korzeń drzewa "tree"
    *result.root.getLeftLeaf() = tree.root;

    return result; // Zwraca wynikową strukturę drzewa po dodaniu
}



template<typename T>
vector<T> CTree<T>::convertToT(vector<string> &values) {
    vector<T> result;

    return result;
}

#endif //UNTITLED_CTREE_H
