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

string removeSpaces(string str){
    str.erase(0, 1);
    return str;
}

int main(){
    ifstream cinemasArq;
    cinemasArq.open("dados/cinemas.txt");

    vector<Cinema> cinemas;
    Cinema cinema;

    string linha;
    string seg;
    vector<string> seglist;
    getline(cinemasArq, linha);

    int idxCol = 0;
    while(getline(cinemasArq, linha)){
        stringstream teste(linha);
        while(getline(teste, seg, ',')){
            seg = removeSpaces(seg);
            switch (idxCol){
            case 0:
                cinema.setCinema_id(seg);
                break;
            case 1:
                cinema.setNome(seg);
                cout << (seg);
                break;
            case 2:
                cinema.setCord_x(stoi(seg));
                break;
            case 3:
                cinema.setCord_y(stoi(seg));
                break;
            case 4:
                // cinema.setPreco(stof(seg));
                break;
            default:
                if((seg)[0] == 'c'){
                    idxCol = -1;
                    break;
                }
                else
                    cinema.setFilmes_exibicao(seg);
            }
            idxCol++;
            // seglist.push_back(removeSpaces(seg));
        }
        cinemas.push_back(cinema);
        // cout << cinema.getCinema_id();
        // cout << "!!!";
    }    
}
