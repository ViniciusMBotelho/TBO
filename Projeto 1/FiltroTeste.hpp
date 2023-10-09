#include"Util.hpp"

class FiltroTeste {
    public:
        static void buscaFilme(vector<Filme> (&filmes)[HASH_CONST], vector<Filme> (&filmesFiltro)[HASH_CONST], string tipo, int duraInf, int duraSup, vector<string> generos, int anoInf, int anoSup){
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
                        if(duraInf != -2 && duraSup != -2){ //verifica se o filtro foi selecionado
                            if((duraInf > filme.getRuntimeMinutes() || duraSup < filme.getRuntimeMinutes())){//verifica se o filme nao esta entre o intervalo proposto
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

                // action, drama
                if(!generos.empty()){
                    for(Filme* filme: cinema.getFilmes_exibicao()){
                        for(string genero: generos){
                            if(filme == nullptr || !buscaString(filme->getGenres(), genero)){
                                confirmacao = false;
                                continue;
                            }
                            else{
                                confirmacao = true;
                                break;
                            }
                        }
                    }
                }


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
