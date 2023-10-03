#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<chrono>
#include<algorithm>
#include"Filme.hpp"

using namespace std;

void imprime(vector<Filme> (&filmes)[100]);

string removeSpace(string str);

int main(){
    //inicio da contagem do tempo do programa
    auto start = chrono::high_resolution_clock::now();
    vector<Filme> filmes[100];
    Filme filmeAux;

    string coluna;
    string linha;

    ifstream cinemasArq;
    cinemasArq.open("dados/filmesCrop.txt");

    if(!cinemasArq.is_open()){
        std::cout << "NAO ABERTO" << endl;
    }
    
    //remover a primeira linha
    getline(cinemasArq, linha);
    linha.clear();

    stringstream ssLinha;
    
    int i=0;


    while(getline(cinemasArq, linha) && i<100){
        
        Filme filme;
        ssLinha.str(linha);
        
        getline(ssLinha, coluna, '\t'); //tconst
        filme.setTconst(coluna);

        //retirar o 'tt' do tconst
        filme.setHash(stoi(removeSpace(coluna))); //hash

        getline(ssLinha, coluna, '\t'); //tittletype
        filme.setTitleType(coluna);
        
        getline(ssLinha, coluna, '\t'); //primarytittle
        filme.setPrimaryTitle(coluna);

        getline(ssLinha, coluna, '\t'); //originaltittle
        filme.setOriginalTitle(coluna);

        getline(ssLinha, coluna, '\t'); //isadult
        if(isdigit(coluna[0]))
            filme.setIsAdult(stoi(coluna));
        else
            filme.setIsAdult(-1);

        getline(ssLinha, coluna, '\t'); //startYear
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

        getline(ssLinha, coluna); //genres
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
        ssLinha.clear();

        filmes[filme.getHash()].push_back(filme);
        i++;
    }
    //printar os filmes
    imprime(filmes);

    cinemasArq.close();

    //termino da contagem do tempo do programa
    auto end = chrono::high_resolution_clock::now();
    // Calcular a duração da execução
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    // Imprimir o tempo de execução em milissegundos
    std::cout << "Tempo de execucao: " << duration.count() << " milissegundos" << endl;
}

void imprime(vector<Filme> (&filmes)[100]){
    for(vector<Filme> filmeHash : filmes){
        std::cout << endl;
        
        for(Filme filme : filmeHash){
            std::cout << filme.getTconst()<<" ";
            std::cout << filme.getTitleType()<<" ";
            std::cout << filme.getPrimaryTitle()<<" ";
            std::cout << filme.getOriginalTitle()<<" ";
            std::cout << filme.getIsAdult()<<" ";
            std::cout << filme.getStartYear()<<" ";
            std::cout << filme.getEndYear()<<" ";
            std::cout << filme.getRuntimeMinutes()<<" ";

            for(string genero: filme.getGenres()){
                std::cout << genero << " ";
            }

            std::cout << endl;
        }
    }
}

string removeSpace(string str){  // apaga o primeiro caracter (espaço em branco)
    str.erase(0, 2);
    return str;
}