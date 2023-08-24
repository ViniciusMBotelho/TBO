#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>

using namespace std;

class No{
	public:
		No* prox;
		int val;
};

class Lista{

	private:
		int tam = 0;
		No* cabeca;

	public:
		// OK
		bool iniciaLista(){

			cabeca = new No;
			cabeca->prox = nullptr;
			tam = 0;

			if(!cabeca){
				return false;
			}
			
			return true;
		}

		// OK
		void inserePos(No* noPred, int val){

			No* novoNo = new No;
			novoNo->val = val;

			novoNo->prox = noPred->prox;  //seg fault aqui
			noPred->prox = novoNo;

			tam++;
		}

		// OK
		void aleatorio(int tam, int min, int max){
			
			srand(time(NULL));
			int num;
			for(int i=0; i<tam; i++){
				num = rand() % (max-min + 1) + min;
				inserePos(buscaNoPred(i), num);
			}
			tam = tam;
		}

		// OK
		No* busca(int val){
			int acessos = 0;
			No* noLista = cabeca->prox;

			while(noLista != nullptr){
				if(noLista->val == val){
					cout << "Valor: " << val << " encontrado\n";
					cout << "Posicao: "<< acessos << " no vetor\n";
					cout << "Acessos: " << acessos+1 << endl;
					return noLista;
				}
				acessos++;
				noLista = noLista->prox; 
			}
			cout << "Valor " << val << " nao encontrado!" << endl;
			return nullptr;
		}

		// OK
		void transposicao(No* n1, No* n2){

			int tmp = n1->prox->val;
			n1->prox->val = n2->prox->val;
			n2->prox->val = tmp;
		}

		// OK
		No* buscaNoPred(int idx){

			No* aux = cabeca->prox;
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

		// OK
		void imprime(){
			No* noAux = cabeca->prox;

			for(int i=0; i<tam; i++){
				cout << noAux->val << " ";
				noAux = noAux->prox;
			}
			cout << endl;
		}

		// OK
		void imprimeRec(No* noAux){
			
			if(noAux == nullptr){
				return ;
			}

			imprimeRec(noAux->prox);
			cout << noAux->val << " ";
		}

		// OK
		void imprimeInv(){
			
			No* noAux = cabeca->prox;
			imprimeRec(noAux);
			cout << endl;
		}

		// OK
		int minimo(int &acessos, int &indice){
			
			No* noAux = cabeca->prox;
			int min = noAux->val;
			acessos = 0;
			
			while(noAux != NULL){
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
