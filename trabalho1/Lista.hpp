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

		// pos precisa ser ponteiro do predecessor
		void inserePos(No* noPred, int val){

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

			tam++;
		}

		// OK
		void aleatorio(int tam, int min, int max){
			
			srand(time(NULL));
			int num;
			for(int i=0; i<tam; i++){
				num = rand() % (max-min + 1) + min;
				inserePos(i, num);
			}
			tam = tam;
		}

		// TUDO CAGADO
		No* busca(int val, int &acessos){  // não entendi a parte de contar o numero de acessos a estrutura
			acessos = 1;
			No* noAux = cabeca->prox;

			for(int i=0; i<tam; i++){
				acessos++;
				if(noAux && noAux->val == val)
					return noAux;
				noAux = noAux->prox;
			}
			cout << "Valor " << val << " nao encontrado, ";
			return nullptr;
		}

		// OK
		void transposicao(No* n1, No* n2){

			// if(ref1 == nullptr || ref2 == nullptr)
			// 	return;

			int tmp = n1->val;
			n1->val = n2->val;
			n2->val = tmp;
		}

		// OK
		No* buscaNo(int idx){
			No* noAux = cabeca->prox;
			for(int i=0; i<idx; i++){
				noAux = noAux->prox;
			}
			return noAux;
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
		void imprimeRec(No* noAux, int tamInv){
			
			if(tamInv == 0){
				return ;
			}

			imprimeRec(noAux->prox, tamInv-1);
			cout << noAux->val << " ";
		}

		// OK
		void imprimeInv(){
			
			No* noAux = cabeca->prox;
			int tamInv = tam;
			imprimeRec(noAux, tamInv);
			cout << endl;
		}

		// testar
		No* minimo(){  // numero de acessos nos campos???

			No* noAux = cabeca->prox;
			No* minRef = noAux;
			unsigned long acessos = 0;

			while(noAux != NULL){
				if(noAux->val < minRef->val)
					minRef = noAux;

				noAux = noAux->prox;
				acessos++;
			}
			cout << acessos << " acessos para encontrar o minimo" << endl;
			return minRef;
		}
};
