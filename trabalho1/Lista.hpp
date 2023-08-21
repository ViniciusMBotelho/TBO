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
		int tam;
		No* cabeca;

	public:
		bool iniciaLista(){
			cabeca = new No;
			cabeca->prox = NULL;
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

		No* busca(int val, int &acessos){  // não entendi a parte de contar o numero de acessos a estrutura
			
			acessos = 1;
			No* noAux = cabeca;
			for(int i=0; i<tam; i++){
				acessos++;
				noAux = noAux->prox;
				if(noAux->val == val)
					return noAux;
			}
			cout << "Valor " << val << " nao encontrado" << endl;
			return nullptr;
		}

		void transposicao(int n1, int n2){
			
			int acessos;
			No* ref1 = busca(n1, acessos);
			No* ref2 = busca(n2, acessos);

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
			
			vector<No*> vetRef;
			No* noAux = cabeca->prox;
			
			//cria um array de referências dos nós
			for(int i=0; i<tam; i++){
				vetRef.push_back(noAux);
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
