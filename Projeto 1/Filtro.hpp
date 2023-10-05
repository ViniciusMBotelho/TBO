#include"Util.hpp"

class Filtro{
    public:
        static void tipo(vector<Filme> (&filmes)[HASH_CONST], vector<Filme> (&filmesFiltro)[HASH_CONST], vector<string> tipos){
            int hashTmp;
            for(vector<Filme> hash: filmes){
                for(Filme filme: hash){
                    if(filme.getTitleType().compare(tipos[0]) == 0){
                        hashTmp = filme.getTconst() % 100;
                        filmesFiltro[hashTmp].push_back(filme);
                    }
                }
            }
        }

        static void tipoEx(vector<Filme> (&filmesFiltro)[HASH_CONST], vector<string> tipos){
            // testando o tempo de execução removendo os elementos da lista ao invés de preencher

            int i = 0;
            int hashTmp;
            for(vector<Filme> hash: filmesFiltro){
                for(Filme filme: hash){
                    if(filme.getTitleType().compare(tipos[0]) != 0){
                        hashTmp = filme.getTconst() % 100;
                        hash.erase(1);
                    }
                    i++;
                }
                i=0;
            }
        }
};
