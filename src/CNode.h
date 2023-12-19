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

    string subtract(string string1, const string& string2);

    string multiply(string string1, string string2);

    string divider(string string1, const string& string2);
};

template<typename T>
string CNode<T>::divider(string string1, const string& string2) {
    // Pętla usuwająca wystąpienia string2 z string1
    while(string1.find(string2) != string::npos) {
        // Usunięcie podciągu string2 z string1, rozpoczynając od pozycji pojawienia się string2 + 1
        // Usunięcie długości string2 - 1 znaków
        string1.erase(string1.find(string2) + 1, string2.length() - 1);
    }
    return string1; // Zwrócenie zmodyfikowanego string1
}


template<typename T>
string CNode<T>::multiply(string string1, string string2) {
    string result; // Inicjacja pustego stringa 'result', do którego będą dodawane zmodyfikowane znaki

    // Pętla iterująca przez znaki w 'string1'
    for(int i = 0; i < string1.length(); ++i) {
        // Jeśli znak z 'string1' jest równy pierwszemu znakowi z 'string2'
        if(string1[i] == string2[0]) {
            result += string2; // Dodaj 'string2' do 'result'
        } else {
            result += string1[i]; // Dodaj znak z 'string1' do 'result'
        }
    }
    return result; // Zwróć zmodyfikowany string 'result'
}


template<typename T>
string CNode<T>::subtract(string string1, const string& string2) {
    // Sprawdzenie czy 'string2' znajduje się w 'string1'
    if (string1.find(string2) == string::npos) {
        return string1; // Jeśli nie, zwróć oryginalny 'string1'
    }

    // Usunięcie ostatniego wystąpienia 'string2' z 'string1'
    string1.erase(string1.rfind(string2), string2.length());

    return string1; // Zwróć zmodyfikowany 'string1'
}


template<typename T>
bool CNode<T>::isValue(const string &s) {
    return false;
}

template<>
bool CNode<string>::isValue(const string &s) {
    if (s.empty()) // Sprawdzenie czy string jest pusty
        return false;

    // Sprawdzenie czy string jest otoczony cudzysłowami (") na początku i na końcu
    if (s[0] != '"' || s[s.length() - 1] != '"')
        return false;

    return true; // Jeśli warunki są spełnione, zwróć true - string jest uznawany za wartość
}


template<>
bool CNode<double>::isValue(const string &s) {
    if (s.empty()) // Sprawdzenie, czy string jest pusty
        return false;

    bool flag = false; // Zmienna flagowa, która śledzi wystąpienie kropki dziesiętnej

    for (size_t i = 0; i < s.length(); ++i) {
        // Sprawdzenie, czy znak nie jest cyfrą ani nie jest kropką dziesiętną lub czy kropka już wystąpiła
        if (!isdigit(s[i]) && (s[i] != '.' || flag))
            return false;

        if(s[i] == '.') // Jeśli znaleziono kropkę, ustaw flagę na true
            flag = true;
    }

    return true; // Jeśli warunki są spełnione, zwróć true - string jest uznawany za wartość double
}


template<>
bool CNode<int>::isValue(const string &s) {
    if (s.empty()) // Sprawdzenie, czy string jest pusty
        return false;

    for (size_t i = 0; i < s.length(); ++i) {
        if (!isdigit(s[i])) // Sprawdzenie, czy każdy znak w stringu jest cyfrą
            return false;
    }

    return true; // Jeśli warunek jest spełniony, zwróć true - string jest uznawany za wartość int
}


template<typename T>
int CNode<T>::whichTypeOfT(const string &statement) {
    if (isValue(statement)) // Sprawdzenie, czy statement jest wartością
        return 0; // Jeśli tak, zwróć 0 - oznacza wartość

    if (statement == "+") // Sprawdzenie, czy statement to operator dodawania
        return 2; // Jeśli tak, zwróć 2 - oznacza operator dodawania

    if (statement == "-") // Sprawdzenie, czy statement to operator odejmowania
        return 3; // Jeśli tak, zwróć 3 - oznacza operator odejmowania

    if (statement == "*") // Sprawdzenie, czy statement to operator mnożenia
        return 4; // Jeśli tak, zwróć 4 - oznacza operator mnożenia

    if (statement == "/") // Sprawdzenie, czy statement to operator dzielenia
        return 5; // Jeśli tak, zwróć 5 - oznacza operator dzielenia

    return 1; // Jeśli statement nie jest wartością ani operatorem, zwróć 1 - oznacza inny typ (np. zmienną)
}



template<>
string CNode<string>::stringToT(string &str) {
    // Usunięcie wszystkich cudzysłowów z ciągu str
    str.erase(remove(str.begin(), str.end(), '"'), str.end());

    return str; // Zwróć zmodyfikowany ciąg str
}


template<>
int CNode<int>::stringToT(string &str) {
    int result; // Zmienna, do której będzie przypisana wartość po konwersji

    stringstream convert(str); // Tworzenie strumienia stringstream z ciągu str

    // Konwersja ciągu na liczbę całkowitą
    if (!(convert >> result)) {
        result = 0; // W przypadku nieudanej konwersji przypisz wartość domyślną (0)
    }

    return result; // Zwróć skonwertowaną liczbę całkowitą
}


template<>
double CNode<double>::stringToT(string &str) {
    double result; // Zmienna, do której będzie przypisana wartość po konwersji

    stringstream convert(str); // Tworzenie strumienia stringstream z ciągu str

    // Konwersja ciągu na liczbę zmiennoprzecinkową
    if (!(convert >> result)) {
        result = 0; // W przypadku nieudanej konwersji przypisz wartość domyślną (0)
    }

    return result; // Zwróć skonwertowaną liczbę zmiennoprzecinkową
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
    type = whichTypeOfT(statement); // Określenie typu węzła na podstawie przekazanego wyrażenia

    if (type == 0) { // Jeśli wyrażenie jest wartością
        this->value = stringToT(statement); // Konwersja wyrażenia na odpowiedni typ i przypisanie do wartości węzła
    } else { // Jeśli wyrażenie to operator lub zmienna
        this->operationOrVariable = statement; // Przypisanie wyrażenia jako operatora lub zmiennej
    }
}


template <typename T>
CNode<T>::CNode(vector<string> &exp, int *index) {
    (*index)++; // Zwiększenie indeksu, aby przejść do kolejnego elementu wektora

    type = whichTypeOfT(exp[*index]); // Określenie typu węzła na podstawie elementu wektora o danym indeksie
    this->operationOrVariable = exp[*index]; // Przypisanie danego elementu jako operatora lub zmiennej

    if (type == 0) { // Jeśli element jest wartością
        this->value = stringToT(exp[*index]); // Konwersja elementu na odpowiedni typ i przypisanie do wartości węzła
    } else if (type > 5) { // Jeśli element jest innym typem niż wartość lub podstawowy operator
        children.push_back(CNode(exp, index)); // Tworzenie węzła dla danego elementu i dodanie go jako dziecka tego węzła
    } else if (type > 1) { // Jeśli element jest operatorem
        children.push_back(CNode(exp, index)); // Tworzenie węzła dla pierwszego elementu i dodanie go jako dziecka tego węzła
        children.push_back(CNode(exp, index)); // Tworzenie węzła dla drugiego elementu i dodanie go jako kolejnego dziecka tego węzła
    }
}

template <>
string CNode<string>::compute(vector<string> variables, vector<string> values) {
    switch (type) {
        case 0: // Jeśli typ węzła to wartość, zwraca wartość tego węzła
            return value;
        case 1: {
            // Jeśli typ węzła to zmienna, znajduje indeks zmiennej w wektorze zmiennych i zwraca odpowiadającą jej wartość z wektora wartości
            int index = find(variables.begin(), variables.end(), operationOrVariable) - variables.begin();
            return values[index];
        }
        case 2: // Jeśli typ węzła to dodawanie, zwraca sumę wartości obliczonych dla lewego i prawego dziecka
            return children[0].compute(variables, values) + children[1].compute(variables, values);
        case 3: // Jeśli typ węzła to odejmowanie, zwraca różnicę wartości obliczonych dla lewego i prawego dziecka
            return subtract(children[0].compute(variables, values), children[1].compute(variables, values));
        case 4: // Jeśli typ węzła to mnożenie, zwraca iloczyn wartości obliczonych dla lewego i prawego dziecka
            return multiply(children[0].compute(variables, values), children[1].compute(variables, values));
        case 5: // Jeśli typ węzła to dzielenie, zwraca wynik dzielenia wartości obliczonych dla lewego i prawego dziecka
            return divider(children[0].compute(variables, values), children[1].compute(variables, values));
    }

    return ""; // Jeśli typ węzła jest nieznany, zwraca pusty string
}

template <typename T>
T CNode<T>::compute(vector<string> variables, vector<T> values) {
    switch (type) {
        case 0: // Jeśli typ węzła to wartość, zwraca wartość tego węzła
            return value;
        case 1: {
            // Jeśli typ węzła to zmienna, znajduje indeks zmiennej w wektorze zmiennych i zwraca odpowiadającą jej wartość z wektora wartości
            int index = find(variables.begin(), variables.end(), operationOrVariable) - variables.begin();
            return values[index];
        }
        case 2: // Jeśli typ węzła to dodawanie, zwraca sumę wartości obliczonych dla lewego i prawego dziecka
            return children[0].compute(variables, values) + children[1].compute(variables, values);
        case 3: // Jeśli typ węzła to odejmowanie, zwraca różnicę wartości obliczonych dla lewego i prawego dziecka
            return children[0].compute(variables, values) - children[1].compute(variables, values);
        case 4: // Jeśli typ węzła to mnożenie, zwraca iloczyn wartości obliczonych dla lewego i prawego dziecka
            return children[0].compute(variables, values) * children[1].compute(variables, values);
        case 5: // Jeśli typ węzła to dzielenie, zwraca wynik dzielenia wartości obliczonych dla lewego i prawego dziecka
            return children[0].compute(variables, values) / children[1].compute(variables, values);
    }

    return 0; // Jeśli typ węzła jest nieznany, zwraca 0
}


template <typename T>
void CNode<T>::printPreorderTraverse() {
    cout << toString() << " "; // Wypisz wartość bieżącego węzła

    for (CNode child : getChildren()) { // Dla każdego dziecka bieżącego węzła
        child.printPreorderTraverse(); // Rekurencyjnie wykonaj pre-order traverse dla dziecka
    }
}


template <typename T>
CNode<T>* CNode<T>::getLeftLeaf() {
    if(children.empty()) // Jeśli węzeł nie ma dzieci, zwraca wskaźnik do bieżącego węzła (liścia)
        return this;
    return children[0].getLeftLeaf(); // W przeciwnym razie rekurencyjnie szuka najbardziej lewego liścia w pierwszym dziecku
}


template <typename T>
string CNode<T>::toString() const {
    if (type == 0) { // Jeśli typ węzła to wartość
        stringstream valueToStr;
        valueToStr << value; // Konwertuje wartość węzła na string przy użyciu strumienia stringstream
        return valueToStr.str(); // Zwraca wartość jako string
    }

    return operationOrVariable; // Jeśli typ węzła to inny niż wartość, zwraca operator lub zmienną
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

template<typename T>
T CNode<T>::stringToT(string &str) {
    cout << "This should never happen" << endl;
    T result;
    return result;
}
#endif //UNTITLED_CNODE_H
