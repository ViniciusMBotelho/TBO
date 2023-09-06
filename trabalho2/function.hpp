#include<iostream>
#include<vector>
using namespace std;

//*************************************************IMPRIMET**************************************************************

void imprime(vector<int> vec){
  for(long unsigned int i=0; i<vec.size(); i++)
      cout << vec[i] << " ";
    cout << endl;
}

//**********************************************INSERTION SORT***********************************************************

void insertionSort(vector<int> vec, int tam, bool aleatorio){
    
    int comp = 0;
    int i, valor, j;
    for (i = 1; i < tam; i++) {
        valor = vec[i];
        j = i - 1;
        while (j >= 0 && vec[j] > valor) {
            comp+=2;
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = valor;
        comp++;
        if(!aleatorio)
            imprime(vec);  // imprime repetidamente
    }
    comp = comp + (tam-1);
    if(aleatorio)  // imprime uma só vez
        imprime(vec);
    cout << "Comparações: " << comp << endl << "--------------------------------------------------------------" << endl;
}

//**********************************************SELECTION SORT***********************************************************

void selectionSort(vector<int> vec, int tam, bool aleatorio){

    int comp = 0;
    int idx = 0;
    for(int i=0; i<tam; i++){
        idx = i;
        for(int j=i+1; j<tam; j++){
            if(vec[idx] > vec[j])
                idx = j;   
        }
        // swap
        int aux = vec[i];
        vec[i] = vec[idx];
        vec[idx] = aux;
        
        comp += (tam-i-1);  // acessos
        if(!aleatorio)
            imprime(vec);  // imprime repetidamente
    }
    if(aleatorio)  // imprime uma só vez
        imprime(vec);
    cout << "Comparações: " << comp << endl << "--------------------------------------------------------------" << endl;
}

//**********************************************GERA ALEATORIA***********************************************************

void criaAleatoria(bool opcao){
    
    vector<int> vAle;
    if(opcao==true){

        for(int i=1; i<=100; i++){
            for(int j=1; j<=i; j++){
                vAle.push_back((rand() % 20) + 1);
            }
            imprime(vAle);
            selectionSort(vAle, vAle.size(), true);
            vAle.clear();
        }
    }else{

        for(int i=1; i<=100; i++){
            for(int j=1; j<=i; j++){
                vAle.push_back((rand() % 20) + 1);
            }
            imprime(vAle);
            insertionSort(vAle, vAle.size(), true);
            vAle.clear();
        }
    }
}