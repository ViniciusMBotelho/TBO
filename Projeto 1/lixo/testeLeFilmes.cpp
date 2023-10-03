#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Filmes.hpp"

using namespace std;

string removeSpaces(string str)
{
  str.erase(0, 1);
  return str;
}

int main()
{
  ifstream cinemasArq;
  cinemasArq.open("dados/filmesCrop.txt");

  vector<Filme> filmes;
  Filme filme;

  string linha;
  string seg;
  vector<string> seglist;
  getline(cinemasArq, linha);

  int i = 0;
  int idxCol = 0;
  while (getline(cinemasArq, seg, '\t')){

    // cout << seg << "--";

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
      if (isdigit(seg[0]))
        filme.setIsAdult(stoi(seg));
      else
        filme.setIsAdult(-1);
      break;
    case 5:
      if (isdigit(seg[0]))
        filme.setStartYear(stoi(seg));
      else
        filme.setStartYear(-1);
      break;
    case 6:
      if (isdigit(seg[0]))
        filme.setEndYear(stoi(seg));
      else
        filme.setEndYear(-1);
      break;
    case 7:
      if (isdigit(seg[0]))
        filme.setRuntimeMinutes(stoi(seg));
      else
        filme.setRuntimeMinutes(-1);
      break;
    default:
      string generoAux;
      stringstream segAux(seg);
      while (getline(segAux, generoAux, ',')){
        // cout << generoAux<<"--";
        filme.setGenres(generoAux);
      }
    }
    idxCol++;
    i++;
  }

  // cout << filme.getTconst() << " " << filme.getTitleType() << " " << filme.getPrimaryTitle() << " "<<filme.getOriginalTitle()<<" "<<filme.getIsAdult()<<" "<<filme.getStartYear()<<" "<<filme.getEndYear()<<" "<<filme.getRuntimeMinutes() <<endl;

  if (i % 10 == 0)
    cout << i << " ";

  idxCol = 0;
  filmes.push_back(filme);
  cout << " ACABOU";
}
