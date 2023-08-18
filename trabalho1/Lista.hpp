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
			No* cabeca = new No;
			cabeca->prox = NULL;
			cauda = cabeca;
			tam = 0;

			// false se n alocar (fazer) 
			return true;
		}

		bool inserePos(int pos, int val){
			if(pos > tam)
				return false;
			
			No* novoNo = new No;
			novoNo->val = val;
			int i;

			//lista vazia
			if(cabeca->prox == NULL){
				cabeca->prox = novoNo;
				novoNo->prox = NULL;
			}
			else{  // lista não vazia
				No* noAux = cabeca;
				for(i=0; i<pos; i++){
					noAux = noAux->prox;
				}
				novoNo->prox = noAux->prox;
				noAux->prox = novoNo;
			}
			//inseriu na última posição
			cauda = i == pos ? novoNo : cauda;
			tam++;

			return true;
		}

		void imprime(){
			No* noAux = cabeca->prox;

			while(noAux != NULL){
				cout << noAux->val << " ";
				noAux = noAux->prox;
			}
		}
};
