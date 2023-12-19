//
// Created by janek on 26.11.2023.
//

#ifndef UNTITLED_UTILITIES_H
#define UNTITLED_UTILITIES_H

#include <string>
#include <vector>
#include "CTree.h"

using namespace std;


class Utilities {
public:
    static vector<string> convertToVector(string expression);
    static void initialize();
    template<typename T> static CTree<T> executeOperation(string &command, vector<string> &line, CTree<T> &cTree);
    template<typename T> static void bridgeLoop(CTree<T> &cTree);
};

vector<string> Utilities::convertToVector(string expression) {
    // Inicjowanie wektora
    vector<string> table;
    size_t iterator = 0;

    // Pętla parsująca wyrażenie na części i dodająca do wektora
    while (iterator < expression.size()) {
        string part;
        while (iterator < expression.size() && expression[iterator] != ' ') // Parsuje wyrażenie po spacjach
            part += expression[iterator++];

        iterator++;
        if (!part.empty()) // Jeśli część nie jest pusta, dodaje ją do wektora
            table.push_back(part);
    }
    return table; // Zwraca wektor stringów, który zawiera podzielone części wyrażenia
}


// Definicja metody initialize
void Utilities::initialize() {
    // Pętla do wyboru typu drzewa i uruchomienia pętli operacji
    while (true) {
        cout << "Wybierz typ drzewa:" << endl;
        cout << "1. String" << endl;
        cout << "2. Double" << endl;
        cout << "3. Int" << endl;
        cout << "4. Exit" << endl;
        string type;
        cin >> type;
        if (type == "1") {
            CTree<string> tree;
            bridgeLoop(tree);// Wywołanie pętli dla drzewa stringów
        } else if (type == "2") {
            CTree<double> tree;
            bridgeLoop(tree);// Wywołanie pętli dla drzewa zmiennoprzecinkowego
        } else if (type == "3") {
            CTree<int> tree;
            bridgeLoop(tree);// Wywołanie pętli dla drzewa liczb całkowitych
        } else if (type == "4")
            return; // Zakończenie programu
        else
            cout << "Niepoprawny wybór" << endl;
    }
}

template<typename T>
void Utilities::bridgeLoop(CTree<T> &cTree){
    string command;
    while (command != "exit") { // Pętla wykonuje się, dopóki użytkownik nie wprowadzi "exit"
        cout << "Podaj polecenie -> " << endl;
        string expression;

        // Pętla do wprowadzania polecenia
        while(expression.empty()) // Jeśli wprowadzona linia jest pusta, kontynuuj pobieranie polecenia
            getline(cin, expression);

        vector<string> line = convertToVector(expression); // Konwertuje wprowadzoną linię na wektor wyrażeń

        command = line[0]; // Pierwszy element wektora to komenda

        line.erase(line.begin()); // Usuwa pierwszy element wektora, który jest komendą

        if(command != "exit")
            cTree = executeOperation(command, line, cTree); // Wywołuje operację na drzewie na podstawie wprowadzonej komendy i parametrów
    }
}


// Definicja metody executeOperation dla danego typu drzewa
template<typename T>
CTree<T> Utilities::executeOperation(string &command, vector<string> &line, CTree<T> &cTree) {
    if (command == "enter") {
        CTree<T> newCTree(line);// Tworzenie nowego drzewa na podstawie linii
        cout << "Wczytane polecenie: ";
        newCTree.prefixTraverse();// Wyświetlanie drzewa (przechodzenie w porządku prefix)
        return newCTree;// Zwraca nowe drzewo
    } else if (command == "print")
        cTree.prefixTraverse();// Wyświetlanie bieżącego drzewa (przechodzenie w porządku prefix)
    else if (command == "comp")
        cout << cTree.compute(line) << endl;
    else if (command == "vars"){// Wywołanie obliczeń na drzewie
        vector<string> variables = CTree<T>::findVariables(cTree.getRoot());// Znajdowanie zmiennych w drzewie
        for (int i = 0; i < variables.size(); ++i)
            cout << variables[i] << " ";
        cout << endl;
    }
    else if (command == "join") {
        cTree = cTree + CTree<T>(line);// Łączenie drzew
        cTree.prefixTraverse();// Wyświetlanie połączonego drzewa
    }
    else
        cout << "Niepoprawna komenda" << endl;// Wyświetlanie błędu dla niepoprawnej komendy
    return cTree;// Zwraca drzewo
}



#endif //UNTITLED_UTILITIES_H
