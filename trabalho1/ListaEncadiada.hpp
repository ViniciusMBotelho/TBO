#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<vector>
#define CAPACIDADE 100

using namespace std;

class listaCon {
	private: 
        int USO = 0;
        int listaC[CAPACIDADE];
        int listaA[CAPACIDADE];

    public:

        void inicializa(){
            
            for (unsigned i = 0; i < CAPACIDADE; i++){
                listaC[i] = -1;
                listaA[i] = -1;
            }
            
        }

        void leLista(int quant, vector<int> vet){
            
            for (unsigned i = USO; i < quant; i++){
                listaC[USO] = vet[i];
                USO++;   
            } 
        }

        void printLista(bool listaPrincipal){

            if(listaPrincipal){
                for(unsigned i=0; i<USO; i++){
                    cout << listaC[i] << " ";
                }
                    cout << endl;
            }else {
                for(unsigned i=0; i<USO; i++){
                    cout << listaA[i] << " ";
                }
                    cout << endl;
                } 
        }
        
        void printRecursivo(bool listaPrincipal){
            
            if(listaPrincipal)
                printRecursivoC(USO-1);
            else
                printRecursivoA(USO-1);
        }

        void printRecursivoC(int AUX){
            if(AUX<0){
                return;
            }
            cout << listaC[AUX] << " ";
            return printRecursivoC(AUX-1);
        }

        void printRecursivoA(int AUX){

        }

        void randomLista(){
	
            for(unsigned i=0; i<CAPACIDADE; i++){
                listaA[i] = rand()%1000;
            }
        }

        void inserir(int pos, int val){
            
            listaC[pos] = val;

            if(USO<=pos)
                USO = pos+1;
        }

        
};

// void printLista(int lista[]){
// 	for(unsigned i=0; i<TAM; i++){
// 		cout << lista[i] << " ";
// 	}
// 		cout << endl;
// }

// // testando colaborador git

// int* randomLista(int lista[]){
	
// 	for(unsigned i=0; i<TAM; i++){
// 		lista[i] = rand()%100;
// 	}
	
// 	return lista;
// }


// int* lerLista(int lista[], int quant){
	
// 	for(unsigned i=0; i<quant; i++){
// 		cin >> lista[i];
// 	}

// }

// int buscaValor(int lista[], int val){
	
// 	for(unsigned i=0; i<TAM; i++){
// 		if(val == lista[i])
// 			return i;
// 	}
// 	cout << "Valor nao encontrado" << endl;
// }

// void inserePosicao(int lista[], int pos){
//     	if(pos>TAM || pos<0){
//     		cout << "Posicao nao encontrada!!" << endl;
//     	}
// }
