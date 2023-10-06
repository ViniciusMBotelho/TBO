#include"Util.hpp"

class FiltroTeste {
    public:
        static void busca(vector<Filme> (&filmes)[HASH_CONST], vector<Filme> (&filmesFiltro)[HASH_CONST], string tipo, int duracaoInf, int duracaoSup, vector<string> generos, int anoInf, int anoSup){
            int hashTmp;
            
                for(vector<Filme> hash: filmes)
                    for(Filme filme: hash){
                        bool confirmacao = true;

                        if(!(tipo.empty())){//verifica se o filtro foi selecionado
                            if(tipo.compare(filme.getTitleType()) != 0){//verifica se o tipo é diferente do solicitado
                                confirmacao = false;
                                continue;
                            }
                        }
                        if(duracaoInf != -2 && duracaoSup != -2){//verifica se o filtro foi selecionado
                            if(!(duracaoInf <= filme.getRuntimeMinutes() && duracaoSup >= filme.getRuntimeMinutes())){
                                confirmacao = false;
                                continue;
                            }
                        }
                        if(anoInf != -2 && anoSup != -2){  //verifica se o filtro foi selecionado                              
                            if(!((anoInf < filme.getStartYear() || filme.getStartYear() == -1) && anoSup > filme.getEndYear())){
                                confirmacao = false;
                                continue;
                            }
                        }

                        if(confirmacao){
                            hashTmp = filme.getTconst() % HASH_CONST;
                            filmesFiltro[hashTmp].push_back(filme);
                        }
                    }

                     
        }

};