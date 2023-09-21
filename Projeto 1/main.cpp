#include<iostream>
#include<stdlib.h>
#include<fstream>
#include <sstream>
#include<vector>
#include<string>
#include <iostream>
#include <algorithm>
#include "Cinemas.hpp"

using namespace std;

string removeSpace(string str){  // apaga o primeiro caracter (espaço em branco)
    str.erase(0, 1);
    return str;
}

int main(){
    ifstream cinemasArq;
    cinemasArq.open("dados/cinemas.txt");

    vector<Cinema> cinemas;
    string linha;
    string seg;
    vector<string> seglist;
    getline(cinemasArq, linha);  // ignora a primeira linha do txt
    int idxCol = 0;  // indice para qual variável seg será direcioanado
    
    // Realiza a leitura de cinemas e extrais suas variáveis
    while(getline(cinemasArq, linha)){
        stringstream teste(linha);
        Cinema cinema;
        while(getline(teste, seg, ',')){
            switch (idxCol){  // seta cada sub string em sua variável no objeto cinema
            case 0:
                cinema.setCinema_id(seg);
                break;
            case 1:
                cinema.setNome(removeSpace(seg));
                break;
            case 2:
                cinema.setCord_x(stoi(removeSpace(seg)));
                break;
            case 3:
                cinema.setCord_y(stoi(removeSpace(seg)));
                break;
            case 4:
                cinema.setPreco(stof(removeSpace(seg)));
                break;
            default:
                cinema.setFilmes_exibicao(removeSpace(seg));
                break;
            }
            idxCol++;
        }
        idxCol = 0;
        cinemas.push_back(cinema);  // adiciona o filme no vetor
    }
    
}
