#include<iostream>
#include<cstdlib>
#include"Lista.hpp"

using namespace std;
#define TAM  3


int main(){
	
	Lista lista;

	lista.iniciaLista();
	
	int tmp;
	for(int i=0; i<TAM; i++){
		cin >> tmp;
		lista.inserePos(i, tmp);
		cout << "b ";
	}

	lista.imprime();

}
