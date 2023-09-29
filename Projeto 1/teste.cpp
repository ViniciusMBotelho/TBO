#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Cinemas.hpp"

using namespace std;

string removeSpace(string str)
{ // apaga o primeiro caracter (espaço em branco)
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
  getline(cinemasArq, linha); // ignora a primeira linha do txt
  Cinema cinema;

  // Realiza a leitura de cinemas e extrais suas variáveis

  int idxCol = 0;  // indice para qual variável seg será direcioanado
  while (getline(cinemasArq, seg, ',')){
    switch (idxCol){ // seta cada sub string em sua variável no objeto cinema
    case 0:
      cinema.setCinema_id(seg);
      break;
    case 1:
      cinema.setNome(removeSpace(seg));
      break;
    case 2:
      // cout << seg;
      // cinema.setCord_x(stoi(removeSpace(seg)));
      break;
    case 3:
      // cinema.setCord_y(stoi(removeSpace(seg)));
      break;
    case 4:
      // cinema.setPreco(stof(removeSpace(seg)));
      break;
    default:
      if(removeSpace(seg)[0] != 't'){
        // cout << removeSpace(seg) << "--";
        idxCol = -1;
        break;
      }
      else if(removeSpace(seg).find(" ") != string::npos){
        // cout << seg << "--";
        cinema.setFilmes_exibicao(seg);
      }
    }
    idxCol++;
  }
  cinemas.push_back(cinema); // adiciona o filme no vetor

  for (int i = 0; i < cinemas.size(); i++){ // imprime todos filmes exibidos pelos cinemas
    for (int j = 0; j < cinemas[i].getFilmes_exibicao().size(); j++){
      // cout << cinemas[i].getFilmes_exibicao()[j] << " ";
    }
    cout << endl;
  }
}
