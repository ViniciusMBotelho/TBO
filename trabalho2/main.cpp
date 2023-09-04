#include<iostream>
#include<stdlib.h>

using namespace std;

#define TAMALE 100
#define TAM 20

void imprime(int* vet, int tam);
void selectionSort(int *vet, int tam, bool aleatorio);
void criaAleatoria();

int main() {
    

    int vet[TAM] = {70, 5, 12, 8, 99, 72, 1, 15, 20, 91, 14, 61, 66, 41, 81, 88, 16, 21, 34, 90};
    // int vetAle[TAMALE];

    // imprime(vet, TAM);
    // selectionSort(vet, TAM, false);

    //lista aleatoria
    criaAleatoria();

}

void imprime(int* vet, int tam){
  for(int i=0; i<tam; i++)
      cout << vet[i] << " ";
    cout << endl;
}

void selectionSort(int *vet, int tam, bool aleatorio){

    int cont = 0;
    int idx = 0;
    for(int i=0; i<tam; i++){
        idx = i;
        for(int j=i+1; j<tam; j++){
            if(vet[idx] > vet[j])
                idx = j;   
        }
        if(!aleatorio){
            cout << "iteracoes: " << cont << "  |  ";
            imprime(vet, tam);
        }
            cont += tam-i;
            int aux = vet[i];
            vet[i] = vet[idx];
            vet[idx] = aux;
    }
    if(aleatorio){
        cout << "iteracoes: " << cont << "  |  ";
        imprime(vet, tam);
    }
    cont = 0;
}

void criaAleatoria(){

    int vet[TAMALE];
    int uso = 1;

    for(int i=0; i<10; i++){
        for(int j=0; j<uso; j++){
            vet[j] = (rand() % 20) + 1;
        }
        imprime(vet, uso);
        selectionSort(vet, uso, true);
        uso++;
    }
}