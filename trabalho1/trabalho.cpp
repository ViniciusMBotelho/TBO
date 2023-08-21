#include<iostream>
#include<cstdlib>
#include"Lista.hpp"

using namespace std;
#define TAM  3


int main(){
	
	Lista lista1;
	Lista lista2;

	lista1.iniciaLista();
	lista2.iniciaLista();
	
	int tmp;
	for(int i=0; i<TAM; i++){
		cin >> tmp;
		lista1.inserePos(i, tmp);
	}
	cout << "Lista 1: " << endl;
	lista1.imprime();

	lista2.aleatorio(5, 1, 4);
	cout << "Lista 2: " << endl;
	lista2.imprime();

	No* noTmp = lista1.busca(2);
	if(noTmp != nullptr)
		cout << noTmp->val << endl;

	lista1.transposicao(lista1.busca(1), lista1.busca(2));
	lista1.imprime();
	lista1.imprimeInv();
	cout << lista1.minimo()->val << endl;
}
