#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<chrono>
#include<algorithm>
#include"Filme.hpp"
#include"Cinema.hpp"
#define HASH_CONST 100

using namespace std;

void imprime(vector<Filme> (&filmes)[HASH_CONST]);

string removeSpace(string str);

int main(){
    //inicio da contagem do tempo do programa
    auto start = chrono::high_resolution_clock::now();
    
    vector<Filme> filmes[HASH_CONST];
    Filme filmeAux;
    string coluna;
    string linha;
    stringstream ssLinha;
    ifstream filmesArq;

    filmesArq.open("dados/filmesCrop.txt");

    if(!filmesArq.is_open()){
        std::cout << "NAO ABERTO" << endl;
    }
    
    //remover a primeira linha
    getline(filmesArq, linha);
    linha.clear();

    int i=0;

    while(getline(filmesArq, linha)){
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
    // imprime(filmes);

    filmesArq.close();


    for(vector<Filme> hash : filmes){
        cout << hash.size() << " ";
    }



//*************************************************************************************************************************************************************
//********************************CINEMAS 

    ifstream cinemasArq;
    vector<Cinema> cinemas;
    string linhaCinema;
    string colunaCinema;
    int idxCol = 0;  // indice para qual variável colunaCinema será direcioanado
    stringstream sslinhaCinema;
    
    cinemasArq.open("dados/cinemas.txt");

    if(!cinemasArq.is_open()){
        std::cout << "NAO ABERTO" << endl;
    }
    
    //remover a primeira linhaCinema
    getline(cinemasArq, linhaCinema); 
    linhaCinema.clear();
    
    // Realiza a leitura de cinemas e extrais suas variáveis
    while(getline(cinemasArq, linhaCinema)){
        Cinema cinema;
        sslinhaCinema.str(linhaCinema);

        while(getline(sslinhaCinema, colunaCinema, ',')){
            switch (idxCol){  // seta cada sub string em sua variável no objeto cinema
            case 0:
                cinema.setCinema_id(colunaCinema);
                break;
            case 1:
                cinema.setNome(removeSpace(colunaCinema));
                break;
            case 2:
                cinema.setCord_x(stoi(removeSpace(colunaCinema)));
                break;
            case 3:
                cinema.setCord_y(stoi(removeSpace(colunaCinema)));
                break;
            case 4:
                cinema.setPreco(stof(removeSpace(colunaCinema)));
                break;
            default:
                // cinema.setFilmes_exibicao();
                break;
            }
            idxCol++;
        }
        idxCol = 0;
        cinemas.push_back(cinema);  // adiciona o filme no vetor
    }

    // for(int i=0; i<cinemas.size(); i++){  // imprime todos filmes exibidos pelos cinemas
    //     for(int j=0; j<cinemas[i].getFilmes_exibicao().size(); j++){
    //         cout << cinemas[i].getFilmes_exibicao()[j] << " ";
    //     }
    //     cout << endl;
    // }


    //termino da contagem do tempo do programa
    auto end = chrono::high_resolution_clock::now();
    // Calcular a duração da execução
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    // Imprimir o tempo de execução em milissegundos
    std::cout << "Tempo de execucao: " << duration.count() << " milissegundos" << endl;
}

void imprime(vector<Filme> (&filmes)[HASH_CONST]){
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