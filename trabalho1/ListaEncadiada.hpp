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

        int buscaVal(int val, bool listaPrincipal){

            if(listaPrincipal){
                for (unsigned i = 0; i < USO; i++){
                    if(listaC[i]==val){
                        return i;
                    }
                }
                return -1;   
            }else {
                for (unsigned i = 0; i < USO; i++){
                    if(listaA[i]==val){
                        return i;
                    }
                } 
                return -1;
            }
        }

        void printRecursivoC(int AUX){
            
            if(AUX<0){
                return;
            }
            cout << listaC[AUX] << " ";
            return printRecursivoC(AUX-1);
        }

        void printRecursivoA(int AUX){

             if(AUX<0){
                return;
            }
            cout << listaA[AUX] << " ";
            return printRecursivoA(AUX-1);
        }

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
            
            if(listaPrincipal){
                printRecursivoC(USO-1);
                cout << endl;
            }
            else{
                printRecursivoA(USO-1);
                cout << endl;
            }
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

        int busca(bool listaPrincipal, int val){
            
            int acessos = 0;
            if(listaPrincipal){
                if(buscaVal(val, true)!=-1){
                    cout << "Posicao " << buscaVal(val, true) << " no vetor" << endl;
                    return buscaVal(val, true);
                }
                else{
                    cout << "Nao encontrado!" << endl;
                    return USO;
                }


            }else {
                if(buscaVal(val, false)!=-1){
                    cout << "Posicao " << buscaVal(val, false) << " no vetor" << endl;
                    return buscaVal(val, false);
                }
                else{
                    cout << "Nao encontrado!" << endl;
                    return USO;
                }
            }    
        }

        void transposicao(int pos1, int pos2){
            
            if(pos1>USO || pos2>USO){
                cout << "Uma das posicoes nao foi preenchida!" << endl;
                return;
            }
            else{
                int aux;
                aux = listaC[pos1];
                listaC[pos1] = listaC[pos2];
                listaC[pos2] = aux;
                return;
            }
        }

        void menorValor(bool listaPrincipal){

            int menor;
            if(listaPrincipal){
                menor = listaC[0];
                for(unsigned i = 0; i < USO; i++){
                    if(listaC[i] < menor)
                        menor = listaC[i];
                }
                cout << "O menor valor da lista e: " << menor << endl;
                cout << USO << " acessos" << endl;
                return;
            }else{
                menor = listaA[0];
                for(unsigned i = 0; i < USO; i++){
                    if(listaA[i] < menor)
                        menor = listaA[i];
                }
                cout << "O menor valor da lista e: " << menor << endl;
                cout << USO << " acessos" << endl;
                return;
            }  
        }
};
