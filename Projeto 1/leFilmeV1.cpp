#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<chrono>
#include <algorithm>
#include "Filme.hpp"

using namespace std;

int main(){

    //inicio da contagem do tempo do programa
    auto start = chrono::high_resolution_clock::now();

    ifstream cinemasArq;
    cinemasArq.open("dados/teste.txt");

    if(!cinemasArq.is_open()){
        std::cout << "NAO ABERTO" << endl;
    }

    vector<Filme> filmes;
    Filme filmeAux;

    string coluna;
    string linha;
    
    //remover a primeira linha
    getline(cinemasArq, linha);
    linha.clear();

    stringstream ssLinha;
    
    int i=0;

    while(getline(cinemasArq, linha)){
        Filme filme;
        ssLinha.str(linha);
        
        getline(ssLinha, coluna, '\t'); //tconst
        filme.setTconst(coluna);

        getline(ssLinha, coluna, '\t'); //tittletype
        filme.setTitleType(coluna);
        
        getline(ssLinha, coluna, '\t'); //primarytittle
        filme.setPrimaryTitle(coluna);

        getline(ssLinha, coluna, '\t'); //originaltittle
        filme.setOriginalTitle(coluna);

        getline(ssLinha, coluna, '\t');  //isadult
        if(isdigit(coluna[0]))
            filme.setIsAdult(stoi(coluna));
        else
            filme.setIsAdult(-1);

        getline(ssLinha, coluna, '\t');  //startYear
        if(isdigit(coluna[0]))
            filme.setStartYear(stoi(coluna));
        else
            filme.setStartYear(-1);

        getline(ssLinha, coluna, '\t'); //endYear
        if(isdigit(coluna[0]))
            filme.setEndYear(stoi(coluna));
        else
            filme.setEndYear(-1);

        getline(ssLinha, coluna, '\t'); //runtimeminutes
        if(isdigit(coluna[0]))
            filme.setRuntimeMinutes(stof(coluna));
        else
            filme.setRuntimeMinutes(-1);

        getline(ssLinha, coluna);  //genres
        stringstream ssAux;
        string genero;
        ssAux.str(coluna);

        if(coluna.find(',') == string::npos){
            filme.setGenres(coluna);
        }
        else{
            while(getline(ssAux, genero, ',')){
                filme.setGenres(genero);
            }
        }

        // std::cout << filme.getTconst() << " " << filme.getTitleType() << " " << filme.getPrimaryTitle() << " "<<filme.getOriginalTitle()<<" "<<filme.getIsAdult()<<" "<<filme.getStartYear()<<" "<<filme.getEndYear()<<" "<<filme.getRuntimeMinutes() <<endl;
        ssLinha.clear();

        filmes.push_back(filme);
        i++;

        cout << filme.getTconst();
    }

    for(string genero: filmes[206688].getGenres()){
        // cout << genero << " ";
    }

    cinemasArq.close();

    //termino da contagem do tempo do programa
    auto end = chrono::high_resolution_clock::now();
    // Calcular a duração da execução
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    // Imprimir o tempo de execução em milissegundos
    std::cout << "Tempo de execucao: " << duration.count() << " milissegundos" << endl;
}