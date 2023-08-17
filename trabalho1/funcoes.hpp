#include<stdio.h>
#include<iostream>
#include<cstdlib>
#define TAM 3

using namespace std;

void printLista(int lista[]){
	for(unsigned i=0; i<TAM; i++){
		cout << lista[i] << " ";
	}
		cout << endl;
}

// testando colaborador git

int* randomLista(int lista[]){
	
	for(unsigned i=0; i<TAM; i++){
		lista[i] = rand()%100;
	}
	
	return lista;
}


int* lerLista(int lista[], int quant){
	
	for(unsigned i=0; i<quant; i++){
		cin >> lista[i];
	}

}

int buscaValor(int lista[], int val){
	
	for(unsigned i=0; i<TAM; i++){
		if(val == lista[i])
			return i;
	}
	cout << "Valor nao encontrado" << endl;
}

void inserePosicao(int lista[], int pos){
	if(pos>TAM || pos<0){
		cout << "Posicao nao encontrada!!" << endl;
	}

}
