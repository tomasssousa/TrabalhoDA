#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
//#include "../data_structures/Graph.h"


using namespace std;

template<class T>
inline void loadLocations(Graph<T> *graph,const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { // verificar se o ficheiro fornecido como argumento é válido
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Saltar a primeira linha (cabeçalho)

    while (getline(file, line)) {
        stringstream temp(line);
        string location, id, code, parking;
        getline(temp, location, ',');
        getline(temp, id, ',');
        getline(temp, code, ',');
        getline(temp, parking, ',');
        graph->addVertex(stoi(id),location, stoi(parking)); // basta adicionar ao vértice o código e a possibilidade ou não de estacionar
        // é preciso alterar esta parte e a função addVertex para que consiga aceitar um boolean que corresponda à possibilidade ou não de estacionar
    }
    file.close();
}

template<class T>
inline void loadDistances(Graph<T> *graph,const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { // verificar se o ficheiro fornecido como argumento é válido
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Saltar a primeira linha (cabeçalho)

    while (getline(file, line)) {
        stringstream temp(line);
        string location1, location2, driving, walking;
        getline(temp, location1, ',');
        getline(temp, location2, ',');
        getline(temp, driving, ',');
        getline(temp, walking, ',');
        graph->addEdge(stoi(location1), stoi(location2), stoi(driving), stoi(walking)); // adicionar a aresta com as duas distâncias
    }
    file.close();
}

