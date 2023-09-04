#include<iostream>
#include<stdlib.h>
#include<vector>
#include<time.h>

using namespace std;

#define TAMALE 100
#define TAM 20

void imprime(vector<int> vec);
void selectionSort(vector<int> vec, int tam, bool aleatorio);
void criaAleatoria();

int main() {
    // srand(time(NULL));  //descometar isso

    // lista unica
    vector<int> vec = {70, 5, 12, 8, 99, 72, 1, 15, 20, 91, 14, 61, 66, 41, 81, 88, 16, 21, 34, 90};

    imprime(vec);
    selectionSort(vec, TAM, false);

    //lista aleatoria
    criaAleatoria();

}

void imprime(vector<int> vec){
  for(int i=0; i<vec.size(); i++)
      cout << vec[i] << " ";
    cout << endl;
}

void selectionSort(vector<int> vec, int tam, bool aleatorio){

    int cont = 0;
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
        
        cont += (tam-i-1);  // acessos
        if(!aleatorio)
            imprime(vec);  // imprime repetidamente
    }
    if(aleatorio)  // imprime uma só vez
        imprime(vec);
    printf("Comparacoes %d\n", cont);
}

void criaAleatoria(){
    
    vector<int> vAle;

    for(int i=1; i<=10; i++){
        for(int j=1; j<=i; j++){
            vAle.push_back((rand() % 20) + 1);
        }
        imprime(vAle);
        selectionSort(vAle, vAle.size(), true);
        vAle.clear();
    }
}
