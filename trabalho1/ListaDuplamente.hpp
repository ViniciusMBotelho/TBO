#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<experimental/random>

using namespace std;

class NoD{
	public:
		NoD* prox;
        NoD* antec;
		int val;
};

class ListaD{

	private:
		int tam;
		NoD* cabeca;

	public:
		bool iniciaLista(){
			cabeca = new NoD;
			cabeca->prox = cabeca;
			cabeca->antec = cabeca;

			tam = 0;

			// false se n alocar (fazer) 
			return true;
		}

		void inserePos(int pos, int val){
			if(pos > tam)
				return;
			
			NoD* noAux = cabeca;
			NoD* novoNo = new NoD;
			novoNo->val = val;
			int i;

			for(i=0; i<pos; i++){  // para 1 NoD antes
				noAux = noAux->prox;
			}
			novoNo->prox = noAux->prox;
            novoNo->antec = noAux;
			noAux->prox = novoNo;
            novoNo->prox->antec = novoNo;

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

		NoD* busca(int val){  // não entendi a parte de contar o numero de acessos a estrutura

			NoD* noAux = cabeca;
			for(int i=0; i<tam; i++){
				noAux = noAux->prox;
				if(noAux->val == val)
					return noAux;
			}
			cout << "Valor " << val << " nao encontrado" << endl;
			return nullptr;
		}

		void transposicao(int n1, int n2){
			NoD* ref1 = busca(n1);
			NoD* ref2 = busca(n2);

			if(ref1 == nullptr || ref2 == nullptr)
				return;

			int tmp = ref1->val;
			ref1->val = ref2->val;
			ref2->val = tmp;
		}

		void imprime(){
			NoD* noAux = cabeca->prox;

			for(int i=0; i<tam; i++){
				cout << noAux->val << " ";
				noAux = noAux->prox;
			}
			cout << endl;
		}

		void imprimeInv(){
			
			NoD* noAux = cabeca->antec;
			
			while(noAux != cabeca){
				cout << noAux->val << " ";
				noAux = noAux->antec;
			}
		}

		NoD* minimo(){  // numero de acessos nos campos???

			NoD* noAux = cabeca->prox;
			NoD* minRef = noAux;

			while(noAux != cabeca){
				if(noAux->val < minRef->val)
					minRef = noAux;

				noAux = noAux->prox;
			}
			return minRef;
		}
};
