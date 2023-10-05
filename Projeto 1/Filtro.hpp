#include"Util.hpp"

class Filtro{
    public:
        static void tipo(vector<Filme> (&filmes)[HASH_CONST], vector<Filme> (&filmesFiltro)[HASH_CONST], string tipo){
            int hashTmp;
            for(vector<Filme> hash: filmes)
                for(Filme filme: hash)
                    if(filme.getTitleType().compare(tipo) == 0){
                        hashTmp = filme.getTconst() % HASH_CONST;
                        filmesFiltro[hashTmp].push_back(filme);
                    }
        }

        static void genero(vector<Filme> (&filmes)[HASH_CONST], vector<Filme> (&filmesFiltro)[HASH_CONST], vector<string> generos){

            int hashTmp;
            for(vector<Filme> hash: filmes)
                for(Filme filme: hash)
                    for(string generoFilme: filme.getGenres())
                        for(string genero: generos)
                            if(generoFilme.compare(genero) == 0){
                                hashTmp = filme.getTconst() % HASH_CONST;
                                filmesFiltro->push_back(filme);
                                break;
                            }       
        }

        
};
