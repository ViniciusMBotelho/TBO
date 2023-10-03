#include<iostream>
#include<stdlib.h>
#include<fstream>
#include <sstream>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include "Cinema.hpp"

using namespace std;

string removeSpace(string str);

int main(){
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
}

string removeSpace(string str){  // apaga o primeiro caracter (espaço em branco)
    str.erase(0, 1);
    return str;
}