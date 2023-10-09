#include"Util.hpp"

class FiltroTeste {
    public:
        static void buscaFilme(vector<Filme> (&filmes)[HASH_CONST], vector<Filme> (&filmesFiltro)[HASH_CONST], string tipo, vector<int> limitesDuracoes, vector<string> generos, vector<int>limiteAnos){
            int hashTmp;
            bool confirmacao, entrou;
            
                // Filtros filmes
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
                        if(limitesDuracoes[0] != -2 && limitesDuracoes[1] != -2){ //verifica se o filtro foi selecionado
                            if((limitesDuracoes[0] > filme.getRuntimeMinutes() || limitesDuracoes[1] < filme.getRuntimeMinutes())){//verifica se o filme nao esta entre o intervalo proposto
                                confirmacao = false;
                                continue;
                            }
                        }
                        if(limiteAnos[0] != -2 && limiteAnos[1] != -2){  //verifica se o filtro foi selecionado                               
                            if(filme.getStartYear() != -1 && filme.getEndYear() != -1)
                                if(!(filme.getStartYear() >= limiteAnos[0] && filme.getEndYear() <= limiteAnos[1])){
                                    confirmacao = false;
                                    continue;
                                }
                            if(filme.getStartYear() == -1)
                                if(!(limiteAnos[0] <= filme.getEndYear() && limiteAnos[1] >= filme.getEndYear())){
                                    confirmacao = false;
                                    continue;
                                }
                            if(filme.getEndYear() == -1)
                                if(!(limiteAnos[0] <= filme.getStartYear() && limiteAnos[1] >= filme.getStartYear())){
                                    confirmacao = false;
                                    continue;
                                }
                        }
                        // short, action, drama
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


        static void buscaCinema(vector<Cinema> (&cinemas), vector<Cinema> (&cinemasFiltro), vector<string> tipos, vector<string> generos, vector<int> limitesDuracoes, int distancia, float preco, vector<int>limiteAnos){

            bool confirmacao;;

            for(Cinema cinema: cinemas){
                confirmacao = true;

                if(!tipos.empty()){  // filtro tipos
                    for(Filme* filme: cinema.getFilmes_exibicao()){
                        if(filme == nullptr || !buscaString(tipos, filme->getTitleType())){
                            confirmacao = false;
                            continue;
                        }
                        if(buscaString(tipos, filme->getTitleType())){
                            confirmacao = true;
                            break;
                        }
                    }
                }

                // if(!generos.empty()){
                //     for(Filme* filme: cinema.getFilmes_exibicao()){
                //         for(string genero: generos){
                //             if(filme != nullptr || !buscaString(filme->getGenres(), genero)){
                //                 confirmacao = false;
                //                 continue;
                //             }
                //             if(buscaString(filme->getGenres(), genero)){
                //                 confirmacao = true;
                //                 break;
                //             }
                //         }
                //     }
                // }

                if(confirmacao){ //verifica se o cinema atual atende os filtros
                    cinemasFiltro.push_back(cinema);
                }
            }
        }

    private:
        static bool buscaString(vector<string> vetor, string alvo){
            for(string str: vetor){
                if(str.compare(alvo) == 0)
                    return true;
            }
            return false;
        }
};
