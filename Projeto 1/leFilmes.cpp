#include<iostream>
#include<stdlib.h>
#include<fstream>
#include <sstream>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include "Filmes.hpp"
#include <chrono>

using namespace std;

string removeSpaces(string str){
    str.erase(0, 1);
    return str;
}

int main(){

    auto start = chrono::high_resolution_clock::now();
    
    ifstream cinemasArq;
    cinemasArq.open("dados/filmesCrop.txt");

    vector<Filme> filmes;
    Filme filme;

    string linha;
    string seg;
    vector<string> seglist;
    getline(cinemasArq, linha);
    stringstream segAux;
    int i = 0;

    int idxCol = 0;
    while(getline(cinemasArq, linha) && i < 5){
        stringstream teste(linha);
        while(getline(teste, seg, '\t')){
            switch (idxCol){
            case 0:
                filme.setTconst(seg);
                break;
            case 1:
                filme.setTitleType(seg);
                break;
            case 2:
                filme.setPrimaryTitle(seg);
                break;
            case 3:
                filme.setOriginalTitle(seg);
                break;
            case 4:
                if(isdigit(seg[0]))
                    filme.setIsAdult(stoi(seg));
                else
                    filme.setIsAdult(-1);
                break;
            case 5:
                if(isdigit(seg[0]))
                    filme.setStartYear(stoi(seg));
                else
                    filme.setStartYear(-1);
                break;
            case 6:
                if(isdigit(seg[0]))
                    filme.setEndYear(stoi(seg));
                else
                    filme.setEndYear(-1);
                break;
            case 7:
                if(isdigit(seg[0]))
                    filme.setRuntimeMinutes(stoi(seg));
                else
                    filme.setRuntimeMinutes(-1);
                break;
            default:
                bool entrou = false;
                segAux << seg;
                string generoAux;
                //  verifica se há mais de um genero e separa em substring
                while(getline(segAux, generoAux, ',')){
                    filme.setGenres(generoAux);
                    // generoAux.clear();
                    entrou = true;
                }
                //  caso em que há apénas um genero (problema com reconhecimento do delimitador da string)
                if(!entrou){
                    generoAux.assign(seg);
                    filme.setGenres(generoAux);
                    // generoAux.clear();
                }
                // cout << generoAux << endl;
                generoAux.clear();
                break;
            }
            idxCol++;
        }
        // cout << filme.getTconst() << " " << filme.getTitleType() << " " << filme.getPrimaryTitle() << " "<<filme.getOriginalTitle()<<" "<<filme.getIsAdult()<<" "<<filme.getStartYear()<<" "<<filme.getEndYear()<<" "<<filme.getRuntimeMinutes() <<endl;

        i++;
        idxCol = 0;
        filmes.push_back(filme);
    }    

        // cout << filmes[3].getTconst()<<" ";
        // cout << filmes[3].getTitleType()<<" ";
        // cout << filmes[3].getPrimaryTitle()<<" ";
        // cout << filmes[3].getOriginalTitle()<<" ";
        // cout << filmes[3].getIsAdult()<<" ";
        // cout << filmes[3].getStartYear()<<" ";
        // cout << filmes[3].getEndYear()<<" ";
        // cout << filmes[3].getRuntimeMinutes()<<" ";
        // cout << filmes[3].getGenres()[0];

        for(Filme filme: filmes){
            for(string genero: filme.getGenres()){
                cout << genero << ",";
            }
            cout << endl;
        }

        cout << " ACABOU ";

        // Finalizar a contagem de tempo
        auto end = chrono::high_resolution_clock::now();
        // Calcular a duração da execução
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        // Imprimir o tempo de execução em milissegundos
        cout << "Tempo de execucao: " << duration.count() << " milissegundos" << endl;
}
