#include<iostream>
#include<stdlib.h>
#include<vector>
#include<time.h>
#include"function.hpp"

using namespace std;

#define TAMALE 100
#define TAM 20

void imprime(vector<int> vec);
void selectionSort(vector<int> vec, int tam, bool aleatorio);
void criaAleatoria(bool opcao);

int main() {
    // srand(time(NULL));  //descometar isso
    vector<int> vec = {70, 1, 12, 8, 99, 72, 5, 15, 20, 91, 14, 61, 66, 41, 81, 88, 16, 21, 34, 90};

    //**********************************************SELECTION SORT***********************************************************
    cout << endl << "************************SELECTION SORT************************" << endl << endl;
    // lista unica
    cout << ">> LISTA PRINCIPAL" << endl;
    imprime(vec);
    selectionSort(vec, TAM, false);

    //lista aleatoria
    cout << endl << ">> LISTA ALEATORIA" << endl;
    criaAleatoria(true);

    //**********************************************INSERTION SORT***********************************************************
    cout << endl << "************************INSERTION SORT************************" << endl << endl;
    // lista unica
    cout << ">> LISTA PRINCIPAL" << endl;
    imprime(vec);
    insertionSort(vec, TAM, false);

    //lista aleatoria
   cout << endl << ">> LISTA ALEATORIA" << endl;
   criaAleatoria(false);
   
}
