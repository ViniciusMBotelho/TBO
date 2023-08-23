#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<vector>
#define CAPACIDADE 100

using namespace std;

class listaCon {
	private: 
        int USO = 0;
        int lista[CAPACIDADE];

        int buscaVal(int val){

            for (unsigned i = 0; i < USO; i++){
                    if(lista[i]==val){
                        return i;
                    }
                }
                return -1;   
        }

        void printRecursivoC(int AUX){
            
            if(AUX<0){
                return;
            }
            cout << lista[AUX] << " ";
            return printRecursivoC(AUX-1);
        }


    public:

        void inicializa(){
            
            for (unsigned i = 0; i < CAPACIDADE; i++){
                lista[i] = -1;
            } 
        }

        void leLista(int quant, vector<int> vet){
            
            for (unsigned i = USO; i < quant; i++){
                lista[USO] = vet[i];
                USO++;   
            } 
        }

        void printLista(){

                for(unsigned i=0; i<USO; i++){
                    cout << lista[i] << " ";
                }
                    cout << endl;
        }
        
        void printRecursivo(bool listaUSO){
            if(listaUSO == true){
                printRecursivoC(USO-1);
                cout << endl;
            }else {
                printRecursivoC(CAPACIDADE-1);
                cout << endl;
            } 
        }

        void randomLista(){
	
            for(unsigned i=0; i<CAPACIDADE; i++){
                lista[i] = rand()%1000;
            }
        }

        void printAleatorio(){
            for(unsigned i=0; i<CAPACIDADE; i++){
                    cout << lista[i] << " ";
                }
                    cout << endl << endl;
        }

        void insere(int pos, int val){
            int i = pos;
            if(pos<=CAPACIDADE){
                if(lista[pos]==-1){
                    lista[pos] = val;
                    USO++;
                }
                else{
                    while(lista[i]!=-1){
                        i++;
                    }
                    while(i>pos){
                        lista[i] = lista[i-1];
                        i--;
                    }
                    lista[pos] = val;
                    USO++;
                }
            }
        }

        int busca(int val){
            
            int acessos = 0;
                if(buscaVal(val)!=-1){
                    cout << "Posicao " << buscaVal(val) << " no vetor" << endl;
                    return buscaVal(val);
                }
                else{
                    cout << "Nao encontrado!" << endl;
                    return USO;
                } 
        }

        void transposicao(int pos1, int pos2){
            
            if(pos1>USO || pos2>USO){
                cout << "Uma das posicoes nao foi preenchida!" << endl;
                return;
            }
            else{
                int aux;
                aux = lista[pos1];
                lista[pos1] = lista[pos2];
                lista[pos2] = aux;
                return;
            }
        }

        void menorValor(bool listaUSO){

            if(listaUSO == true){  
                int menor;
                menor = lista[0];
                for(unsigned i = 0; i < USO; i++){
                    if(lista[i] < menor)
                        menor = lista[i];
                }
                cout << "O menor valor da lista e: " << menor << endl;
                cout << USO << " acessos" << endl;
                return; 
            }else{
                int menor;
                menor = lista[0];
                for(unsigned i = 0; i < CAPACIDADE; i++){
                    if(lista[i] < menor)
                        menor = lista[i];
                }
                cout << "O menor valor da lista e: " << menor << endl;
                cout << CAPACIDADE << " acessos" << endl;
                return; 
            }
        }
};
