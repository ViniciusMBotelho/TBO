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

class Util{
  public:
    static Filme* movieReference(int filmeId, vector<Filme> (&filmes)[HASH_CONST]){
      
      int hash = filmeId % 100;

      if(filmes[hash].size() != 0){  // hash não vazio

        Filme* fAux = new Filme;
        int inicio = 0;
        int fim = filmes[hash].size() - 1;

        while (inicio <= fim) {  // busca binária
          int meio = inicio + (fim - inicio) / 2;
          if (filmes[hash][meio].getTconst() == filmeId){
            *fAux = filmes[hash][meio];
            return fAux;
          }
          if (filmes[hash][meio].getTconst() < filmeId)
            inicio = meio + 1;
          else
            fim = meio - 1;
        }
      }
        return nullptr;
    }
};