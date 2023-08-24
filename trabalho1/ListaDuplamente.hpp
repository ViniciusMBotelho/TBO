#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<ctime>

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

		//OK
		void imprimeRec(NoD* noAux){
			
			if(noAux == cabeca){
				return ;
			}

			imprimeRec(noAux->prox);
			cout << noAux->val << " ";
		}

	public:

		//OK
		bool iniciaLista(){

			cabeca = new NoD;
			cabeca->prox = cabeca;
			cabeca->antec = cabeca;
			tam = 0;

			if(!cabeca){
				return false;
			}
			
			return true;
		}
		//OK
		 void inserePos(NoD* noPred, int val){

            NoD* novoNo = new NoD;
            novoNo->val = val;

            novoNo->prox = noPred->prox;
            novoNo->antec = noPred;
            noPred->prox = novoNo;
            noPred->antec = novoNo;

            tam++;
        } 
		//OK
		void aleatorio(int tam, int min, int max){
			
			srand(time(NULL));
			int num;
			for(int i=0; i<tam; i++){
				num = rand() % (max-min + 1) + min;
				inserePos(buscaNoPred(i), num);
			}
			tam = tam;
		}
		//OK
		NoD* busca(int val){
			int acessos = 0;
			NoD* noLista = cabeca->prox;

			while(noLista != cabeca){
				if(noLista->val == val){
					cout << "Acessos necessarios: " << acessos << ", valor " << val << " encontrado" << "na posicao " << acessos << endl;
					return noLista;
				}
				acessos++;
				noLista = noLista->prox; 
			}
			cout << "Valor " << val << " nao encontrado!" << endl;
			return nullptr;
		}
		//OK
		NoD* buscaNoPred(int idx){

			NoD* aux = cabeca->prox;
			if(idx == 0){
				return cabeca;
			}

			int i=0;
			while(aux != NULL && i < idx-1){
				aux = aux->prox;
				i++;
			}
			return aux;
		}
		//OK
		void transposicao(NoD* n1, NoD* n2){

			int tmp = n1->prox->val;
			n1->prox->val = n2->prox->val;
			n2->prox->val = tmp;
		}
		//OK
		void imprime(){
			NoD* noAux = cabeca->prox;

			for(int i=0; i<tam; i++){
				cout << noAux->val << " ";
				noAux = noAux->prox;
			}
			cout << endl;
		}
		// OK
		void imprimeInv(){
			
			NoD* noAux = cabeca->prox;
			imprimeRec(noAux);
			cout << endl;
		}
		//OK
		int minimo(int &acessos, int &indice){
			
			NoD* noAux = cabeca->prox;
			int min = noAux->val;
			acessos = 0;
			
			while(noAux != cabeca){
				acessos++;
				if(noAux->val < min){
					min = noAux->val;
					indice = acessos-1;
				}
				noAux = noAux->prox;
			}
			return min;
		}
};
