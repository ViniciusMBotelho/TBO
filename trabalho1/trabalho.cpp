#include<iostream>
#include<cstdlib>
#include<vector>
#include"Lista.hpp"
#include"ListaDuplamente.hpp"
#include"ListaEstatica.hpp"

using namespace std;


int main(){
	
	int tam = 10;
	vector<int> vet = {8, 1, 3, 4, 3, 6, 10, 8, 9, 1};
	int acessos = 0;

	// LISTA SIMPLES

	cout << "LISTA LIGADA SIMPLES" << endl;

	Lista listaS;
	Lista listaSA;

	//inicialização
	listaS.iniciaLista();
	listaSA.iniciaLista();

	//inserindo valores na lista principal
	for(int i=0; i<tam; i++){
		listaS.inserePos(listaS.buscaNo(i-1), vet[i]);
	}
	listaS.imprime();

	//inserindo valores em posições especificas
	listaS.inserePos(10, 11);
	listaS.inserePos(4, 2);
	listaS.inserePos(0, 7);
	listaS.imprime();


	//buscando valores
	// cout << "Encontrado valor " << listaS.busca(10, acessos)->val;
	// cout << ", " << acessos << " acessos necessarios" << endl;
	// cout << "Encontrado valor " << listaS.busca(8, acessos)->val;
	// cout << ", " << acessos << " acessos necessarios" << endl;
	// // ******************IMPORTANTE************** precisa concertar a saida desse proximo cout
	// if(!(listaS.busca(12, acessos))){
	// 	cout << "Valor não existe" << endl;
	// } // assim para tratar o retorno nullptr ???

	// cout << "Encontrado valor " << listaS.busca(12, acessos)->val;
	// cout << ", " << acessos << " acessos necessarios" << endl;

	// imprime recursivo
	// listaS.imprimeInv();

	// transpondo posições da lista
	listaS.transposicao(listaS.buscaNo(3), listaS.buscaNo(4));
	listaS.transposicao(listaS.buscaNo(0), listaS.buscaNo(6));
	// listaS.transposicao(listaS.buscaNo(6), listaS.buscaNo(12));
	cout << "transposto: ";
	listaS.imprime();

	//buscando valor minimo na lista principal
	cout << listaS.minimo()->val << endl;  // Mostra posição do predecessor???

	// cout << endl << endl << "LISTA ENCADEADA ALEATORIA" << endl;
	// //lista aleatoria
	// listaSA.aleatorio(100, 1, 1000);
	// listaSA.imprime();
	// cout << listaSA.minimo()->val << endl;
	// listaSA.imprimeInv();


	// LISTA DUPLAMENTE LIGADA

	// cout << endl << "lISTA DUPLAMENTE LIGADA" << endl;

	// ListaD listaD;
	// ListaD listaDA;

	// listaD.iniciaLista();
	// listaDA.iniciaLista();

	// for(int i=0; i<tam; i++){
	// 	listaD.inserePos(i, vet[i]);
	// }
	// listaD.imprime();

	// listaD.inserePos(10, 11);
	// listaD.inserePos(4, 2);
	// listaD.inserePos(0, 7);
	// listaD.imprime();

	// cout << listaD.busca(10)->val << endl;
	// cout << listaD.busca(8)->val << endl;
	// listaD.busca(12) == nullptr ? cout << "" : cout << listaD.busca(12)->val;  // assim para tratar o retorno nullptr ??? 

	// listaD.transposicao(3, 4);
	// listaD.transposicao(0, 6);
	// listaD.transposicao(6, 12);
	// listaD.imprime();

	// cout << listaD.minimo()->val << endl;  // Mostra posição do predecessor???
	// listaD.imprimeInv();

	// cout << endl << endl << "LISTA DUPLAMENTE ENCADEADA ALEATORIA" << endl;

	// listaDA.aleatorio(100, 1, 1000);
	// listaDA.imprime();
	// cout << listaDA.minimo()->val << endl;
	// listaDA.imprimeInv();


	// LISTA POR CONTIGUIDADE FISICA

	// cout << endl << "lISTA POR CONTIGUIDADE FISICA" << endl;

	// listaCon listaC;
	// listaCon listaA;

	// cout << endl << "**********Lista Principal***********" << endl;
	// //inicializações
	// listaC.inicializa();
	// listaC.leLista(tam, vet);
	// listaC.printLista();
	// //inserir novos valores
	// listaC.insere(10, 11);
	// listaC.insere(4, 2);
	// listaC.insere(0, 7);
	// listaC.printLista();
	// //busca lista principal
	// cout << listaC.busca(10) << " acessos" << endl;
	// cout << listaC.busca(8) << " acessos" << endl;
	// cout << listaC.busca(12) << " acessos" << endl;
	// //transposição lista principal
	// listaC.transposicao(3, 4);
	// listaC.transposicao(0, 6);
	// listaC.transposicao(6, 12);
	// listaC.printLista();
	// //print invertido
	// listaC.printRecursivo(true);
	// //menor valor  da lista
	// listaC.menorValor(true);

	// //lista aleatoria
	// cout << endl << "*************Lista Aleatoria**************" << endl;
	// //inicializações
	// listaA.inicializa();
	// listaA.randomLista();
	// //mostrar lista
	// listaA.printAleatorio();
	// //mostrar lista inversa
	// listaA.printRecursivo(false);
	// //buscar menor valor
	// listaA.menorValor(false);
}