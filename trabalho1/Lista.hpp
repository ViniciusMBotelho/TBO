#include<stdio.h>
#include<iostream>
#include<cstdlib>

using namespace std;

class No{
	public:
		No* prox;
		int val;
};

class Lista{

	private:
		int tam;
		No* cabeca;
		No* cauda;

	public:
		bool iniciaLista(){
			cabeca = new No;
			cabeca->prox = NULL;
			cauda = cabeca;
			tam = 0;

			// false se n alocar (fazer) 
			return true;
		}

		void inserePos(int pos, int val){
			if(pos > tam)
				return;
			
			No* noAux = cabeca;
			No* novoNo = new No;
			novoNo->val = val;
			int i;

			for(i=0; i<pos; i++){  // para 1 no antes
				noAux = noAux->prox;
			}
			novoNo->prox = noAux->prox;
			noAux->prox = novoNo;

			cauda = i == pos ? novoNo : cauda;
			tam++;
		}

		void aleatorio(int tam, int range){
			

		}

		void imprime(){
			No* noAux = cabeca->prox;

			for(int i=0; i<tam; i++){
				cout << noAux->val << " ";
				noAux = noAux->prox;
			}
		}
};
