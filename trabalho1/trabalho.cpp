#include<iostream>
#include<cstdlib>
#include"Lista.hpp"
#include"ListaDuplamente.hpp"

using namespace std;
#define TAM  3


int main(){
	
	// LISTA SIMPLES
	cout << "LISTA LIGADA SIMPLES" << endl;

	Lista listaS;
	int tam = 10;
	int vet[tam] = {8, 1, 3, 4, 3, 6, 10, 8, 9, 1};

	listaS.iniciaLista();

	for(int i=0; i<tam; i++){
		listaS.inserePos(i, vet[i]);
	}
	listaS.imprime();

	listaS.inserePos(10, 11);
	listaS.inserePos(4, 2);
	listaS.inserePos(0, 7);

	listaS.imprime();

	cout << listaS.busca(10)->val << endl;
	cout << listaS.busca(8)->val << endl;
	listaS.busca(12) == NULL ? cout << "" : cout << listaS.busca(12)->val; // assim para tratar o retorno nullptr ??? 

	listaS.transposicao(3, 4);
	listaS.transposicao(0, 6);
	listaS.transposicao(6, 12);
	listaS.imprime();

	cout << listaS.minimo()->val << endl;  // Mostra posição do predecessor???

	// LISTA DUPLAMENTE LIGADA
	cout << endl << "lISTA DUPLAMENTE LIGADA" << endl;

	ListaD listaD;

	listaD.iniciaLista();
	for(int i=0; i<tam; i++){
		listaD.inserePos(i, vet[i]);
	}
	listaD.imprime();

	listaD.inserePos(10, 11);
	listaD.inserePos(4, 2);
	listaD.inserePos(0, 7);
	listaD.imprime();

	cout << listaD.busca(10)->val << endl;
	cout << listaD.busca(8)->val << endl;
	listaD.busca(12) == nullptr ? cout << "" : cout << listaD.busca(12)->val;

	listaD.transposicao(3, 4);
	listaD.transposicao(0, 6);
	listaD.transposicao(6, 12);
	listaD.imprime();

	cout << listaD.minimo()->val << endl;  // Mostra posição do predecessor???
}