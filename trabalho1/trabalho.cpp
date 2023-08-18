#include<iostream>
#include<cstdlib>
#include"funcoes.hpp"

using namespace std;

void printLista(int lista[]);
int* randomLista(int lista[]);
int* lerLista(int lista[], int quant);
int buscaValor(int lista[], int val);
void inserePosicao(int lista[], int pos);

int main(){
	int lista[TAM],opcao,quant;


	randomLista(lista);
	lerLista(lista);
	printLista(lista);
	buscaValor(lista,2);
	inserePosicao(lista,3);


	cin >> opcao;
	switch(opcao){
		case 1:{
			cin >> quant;
			lerLista(lista, quant);
			break;
		} 
	}


	return 0;
}
