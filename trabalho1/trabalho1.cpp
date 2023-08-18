#include<iostream>
#include<cstdlib>
#include"Lista.hpp"

using namespace std;

int main(){
	
	Lista lista;

	lista.iniciaLista();
	lista.inserePos(0, 1);
	lista.inserePos(1, 2);
	lista.inserePos(2, 3);
	lista.imprime();

}
