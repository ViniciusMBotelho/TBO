#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<experimental/random>

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

		void aleatorio(int tam, int min, int max){
			
			srand(time(NULL));
			int num;
			for(int i=0; i<tam; i++){
				num = rand() % (max-min + 1) + min;
				inserePos(i, num);
			}
			tam = tam;
		}

		No* busca(int val){  // não entendi a parte de contar o numero de acessos a estrutura

			No* noAux = cabeca;
			for(int i=0; i<tam; i++){
				noAux = noAux->prox;
				if(noAux->val == val)
					return noAux;
			}
			cout << "Valor " << val << " nao encontrado" << endl;
			return nullptr;
		}

		void transposicao(No* ref1, No* ref2){
			if(ref1 == nullptr || ref2 == nullptr)
				return;

			int tmp = ref1->val;
			ref1->val = ref2->val;
			ref2->val = tmp;
		}

		void imprime(){
			No* noAux = cabeca->prox;

			for(int i=0; i<tam; i++){
				cout << noAux->val << " ";
				noAux = noAux->prox;
			}
			cout << endl;
		}

		void imprimeInv(){
			
			No* vetRef[tam];
			No* noAux = cabeca->prox;
			
			//cria um array de referências dos nós
			for(int i=0; i<tam; i++){
				vetRef[i] = noAux;
				noAux = noAux->prox;
			}
			for(int i=tam-1; i>=0; i--){
				cout << vetRef[i]->val << " ";
			}
			cout << endl;
		}

		No* minimo(){  // numero de acessos nos campos???

			No* noAux = cabeca->prox;
			No* minRef = noAux;

			while(noAux != NULL){
				if(noAux->val < minRef->val)
					minRef = noAux;

				noAux = noAux->prox;
			}
			return minRef;
		}
};
