#include<iostream>
#include<cstdlib>
#include"Lista.hpp"

using namespace std;

int main(){
	
	Lista lista;
	lista.iniciaLista();

	int tmp;
	// for(int i=0; i<3; i++){
	// 	cin >> tmp;
	// }
	lista.inserePos(0, 1);
	lista.inserePos(1, 2);
	lista.inserePos(1, 3);

	lista.imprime();
}
