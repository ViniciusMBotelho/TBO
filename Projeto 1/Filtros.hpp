#include"Util.hpp"

class Filtros {
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
            bool confirmacao;

            for(Cinema cinema: cinemas){
                confirmacao = true;
                
                // filtro de distância
                if(distancia != -2){
                    float distanciaCinema =  sqrt(pow((cinema.getCord_x()), 2) + pow((cinema.getCord_y()), 2));
                    if(distanciaCinema > distancia){
                        confirmacao = false;
                        continue;
                    }
                }

                // filtro de preco
                if(preco != -2){
                    if(cinema.getPreco() > preco){
                        confirmacao = false;
                        continue;
                    }
                }

                if(!(tipos.empty() && generos.empty() && (limitesDuracoes[0] == -2 && limitesDuracoes[1] == -2) && (limiteAnos[0] == -2 && limiteAnos[1] == -2))){

                    for(Filme* filmeRef: cinema.getFilmes_exibicao()){
                        if(filmeRef != nullptr){

                            // filtro de tipos
                            if(!tipos.empty() && !buscaString(tipos, filmeRef->getTitleType())){
                                confirmacao = false;
                                continue;
                            }
                            else if(buscaString(tipos, filmeRef->getTitleType())){
                                confirmacao = true;
                            }

                            // filtro de generos
                            if(!generos.empty()){
                                for(string genero: generos){
                                    if(!buscaString(filmeRef->getGenres(), genero)){
                                        confirmacao = false;
                                        continue;
                                    }
                                    else{
                                        confirmacao = true;
                                    }
                                }
                            }

                            // filtro de duração
                            if(limitesDuracoes[0] != -2 && limitesDuracoes[1] != -2){
                                if((limitesDuracoes[0] > filmeRef->getRuntimeMinutes() || limitesDuracoes[1] < filmeRef->getRuntimeMinutes())){
                                    confirmacao = false;
                                    continue;
                                }
                            }

                            // filtro de anos
                            if(limiteAnos[0] != -2 && limiteAnos[1] != -2){
                                if(filmeRef->getStartYear() != -1 && filmeRef->getEndYear() != -1)
                                    if(!(filmeRef->getStartYear() > limiteAnos[0] && filmeRef->getEndYear() < limiteAnos[1])){
                                        confirmacao = false;
                                        continue;
                                    }
                                if(filmeRef->getStartYear() == -1)
                                    if(!(limiteAnos[0] < filmeRef->getEndYear() && limiteAnos[1] > filmeRef->getEndYear())){
                                        confirmacao = false;
                                        continue;
                                    }
                                if(filmeRef->getEndYear() == -1)
                                    if(!(limiteAnos[0] < filmeRef->getStartYear() && limiteAnos[1] > filmeRef->getStartYear())){
                                        confirmacao = false;
                                        continue;
                                    }
                            }
                        }
                        else{
                            confirmacao = false;
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
