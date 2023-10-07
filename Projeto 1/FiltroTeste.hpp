#include"Util.hpp"

class FiltroTeste {
    public:
        static void busca(vector<Filme> (&filmes)[HASH_CONST], vector<Filme> (&filmesFiltro)[HASH_CONST], string tipo, int duracaoInf, int duracaoSup, vector<string> generos, int anoInf, int anoSup){
            int hashTmp;
            bool confirmacao, entrou;
            
                for(vector<Filme> hash: filmes)
                    for(Filme filme: hash){
                        confirmacao = true;
                        entrou = true;

                        if(!tipo.empty()){ //verifica se o filtro foi selecionado
                            if(tipo.compare(filme.getTitleType()) != 0){//verifica se o tipo é diferente do solicitado
                                confirmacao = false;
                                continue;
                            }
                        }
                        if(duracaoInf != -2 && duracaoSup != -2){ //verifica se o filtro foi selecionado
                            if(!(duracaoInf <= filme.getRuntimeMinutes() && duracaoSup >= filme.getRuntimeMinutes())){//verifica se o filme nao esta entre o intervalo proposto
                                confirmacao = false;
                                continue;
                            }
                        }
                        if(anoInf != -2 && anoSup != -2){  //verifica se o filtro foi selecionado                               
                            if(filme.getStartYear() != -1 && filme.getEndYear() != -1)
                                if(!(filme.getStartYear() >= anoInf && filme.getEndYear() <= anoSup)){
                                    confirmacao = false;
                                    continue;
                                }
                            if(filme.getStartYear() == -1)
                                if(!(anoInf <= filme.getEndYear() && anoSup >= filme.getEndYear())){
                                    confirmacao = false;
                                    continue;
                                }
                            if(filme.getEndYear() == -1)
                                if(!(anoInf <= filme.getStartYear() && anoSup >= filme.getStartYear())){
                                    confirmacao = false;
                                    continue;
                                }
                        }
                        // melhorar a variavel de controle
                        if(!generos.empty()){  //verifica se o filtro foi selecionado
                            for(string generoFilme: filme.getGenres()){
                                for(string genero: generos)
                                    if(generoFilme.compare(genero) == 0 && entrou){
                                        filmesFiltro[hashTmp].push_back(filme);
                                        entrou = false;
                                    }
                            }
                            confirmacao = false;            
                        }

                        if(confirmacao){ //verifica se o filme atual atende os filtros
                            hashTmp = filme.getTconst() % HASH_CONST;
                            filmesFiltro[hashTmp].push_back(filme);
                        }
                    }


        }

};