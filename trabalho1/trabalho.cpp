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
	int indice = 0;

	// LISTA SIMPLES

	cout << "**********Lista Ligada Simples***********" << endl;

	Lista listaS;
	Lista listaSA;

	//INICIALIZAÇÃO
	listaS.iniciaLista();
	listaSA.iniciaLista();

	for(int i=0; i<tam; i++){
		listaS.inserePos(listaS.buscaNoPred(i), vet[i]);
	}
	listaS.imprime();

	// inserindo valores em posições especificas
	listaS.inserePos(listaS.buscaNoPred(10), 11);
	listaS.inserePos(listaS.buscaNoPred(4), 2);
	listaS.inserePos(listaS.buscaNoPred(0), 7);
	listaS.imprime();


	// buscando valores
	(listaS.busca(10));
	(listaS.busca(8));
	(listaS.busca(12));

	// imprime recursivo
	listaS.imprimeInv();

	// transpondo posições da lista
	listaS.transposicao(listaS.buscaNoPred(3), listaS.buscaNoPred(4));
	listaS.transposicao(listaS.buscaNoPred(0), listaS.buscaNoPred(6));
	listaS.transposicao(listaS.buscaNoPred(6), listaS.buscaNoPred(12));
	cout << "transposto: ";
	listaS.imprime();
	// buscando valor minimo na lista principal

	cout << "O menor valor é: " << listaS.minimo(acessos, indice) << ", posicao " << indice << ", formam necessarios " << acessos << " acessos" << endl;

	// cout << endl << endl << "LISTA ENCADEADA ALEATORIA" << endl;
	// //lista aleatoria
	// listaSA.aleatorio(100, 1, 1000);
	// listaSA.imprime();
	// listaSA.imprimeInv();
	// cout << "O menor valor é: " << listaSA.minimo(acessos, indice) << ", posicao " << indice << ", formam necessarios " << acessos << " acessos" << endl;


	// LISTA DUPLAMENTE LIGADA

	// cout << endl << "lISTA DUPLAMENTE LIGADA" << endl;

	// ListaD listaD;
	// ListaD listaDA;

	// //inicialização das listas
	// listaD.iniciaLista();
	// listaDA.iniciaLista();

	// //inserindo valores principais da lista
	// for(int i=0; i<tam; i++){
	// 	listaD.inserePos(listaD.buscaNoPred(i), vet[i]);
	// }
	// listaD.imprime();

	// //inserindo valores em pontos especificos
	// listaD.inserePos(listaD.buscaNoPred(10), 11);
	// listaD.inserePos(listaD.buscaNoPred(4), 2);
	// listaD.inserePos(listaD.buscaNoPred(0), 7);
	// listaD.imprime();

	// //buscando valores e retornando o ponteiro referente a sua posicao
	// (listaD.busca(10));
	// (listaD.busca(8));
	// (listaD.busca(12));

	// //transpondo valores da lista
	// listaD.transposicao(listaD.buscaNoPred(3), listaD.buscaNoPred(4));
	// listaD.transposicao(listaD.buscaNoPred(0), listaD.buscaNoPred(6));
	// listaD.transposicao(listaD.buscaNoPred(6), listaD.buscaNoPred(12));
	// listaD.imprime();

	// //imprimindo lista inversa
	// listaD.imprimeInv();
	// //menor valor da lista
	// cout << "O menor valor é: " << listaD.minimo(acessos, indice) << ", posicao " << indice << ", formam necessarios " << acessos << " acessos" << endl;

	// cout << endl << endl << "LISTA DUPLAMENTE ENCADEADA ALEATORIA" << endl;

	// listaDA.aleatorio(100, 1, 1000);
	// listaDA.imprime();
	// listaDA.imprimeInv();
	// cout << "O menor valor é: " << listaDA.minimo(acessos, indice) << ", posicao " << indice << ", formam necessarios " << acessos << " acessos" << endl;


	// LISTA POR CONTIGUIDADE FISICA

	// cout << endl << "lISTA POR CONTIGUIDADE FISICA" << endl;

	listaCon listaC;
	// listaCon listaA;

	cout << endl << "**********Lista Principal***********" << endl;
	//inicializações
	listaC.inicializa();
	listaC.leLista(tam, vet);
	listaC.printLista();
	//inserir novos valores
	listaC.insere(10, 11);
	listaC.insere(4, 2);
	listaC.insere(0, 7);
	listaC.printLista();
	//busca lista principal
	cout << listaC.busca(10) << " acessos" << endl;
	cout << listaC.busca(8) << " acessos" << endl;
	cout << listaC.busca(12) << " acessos" << endl;
	//transposição lista principal
	listaC.transposicao(3, 4);
	listaC.transposicao(0, 6);
	listaC.transposicao(6, 12);
	listaC.printLista();
	//print invertido
	listaC.printRecursivo(true);
	//menor valor  da lista
	listaC.menorValor(true);

	// //lista aleatoria
	// cout << endl << "*************Lista Aleatoria**************" << endl;
	// //inicializações
	// listaA.inicializa();
	// listaA.randomLista(100, 0, 1000);
	// //mostrar lista
	// listaA.printLista();
	// //mostrar lista inversa
	// listaA.printRecursivo(false);
	// //buscar menor valor
	// listaA.menorValor(false);
}