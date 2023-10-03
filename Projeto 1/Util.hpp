#include<iostream>
#include"Filme.hpp"
#include"Cinema.hpp"
#define HASH_CONST 100

class Util{
  public:
    static Filme* movieReference(int filmeId, vector<Filme> (&filmes)[HASH_CONST]){
      
      Filme* fAux = new Filme;
      int hash = filmeId % 100;

      if(filmes[hash].size() != 0)
        for(Filme filme: filmes[hash])
          if(filmeId == filme.getTconst()){
            *fAux = filme;
            return fAux;
          }
      return nullptr;
    }
};
