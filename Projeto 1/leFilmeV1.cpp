#include"FiltroTeste.hpp"

using namespace std;

void imprime(vector<Filme> (&filmes)[HASH_CONST]);

string removeSpace(string str, int quant);

int main(){
    //inicio da contagem do tempo do programa
    auto start = chrono::high_resolution_clock::now();
    
    //***********FILMES*********** 

    vector<Filme> filmes[HASH_CONST];
    string coluna;
    string linha;
    stringstream ssLinha;
    ifstream filmesArq;
    int i=0;

    filmesArq.open("dados/filmesCrop.txt");
    if(!filmesArq.is_open()){
        std::cout << "NAO ABERTO" << endl;
    }
    
    //remover a primeira linha
    getline(filmesArq, linha);
    linha.clear();

    while(getline(filmesArq, linha)){
        Filme filme;
        ssLinha.str(linha);

        {//Realiza a leitura dos filmes e extrai seus atributos
            getline(ssLinha, coluna, '\t'); //tconst
            filme.setTconst(stoi(removeSpace(coluna, 2)));  //retirar o 'tt' do tconst

            filme.setHash(stoi(removeSpace(coluna, 2))); //hash

            getline(ssLinha, coluna, '\t'); //tittletype
            filme.setTitleType(coluna);
            
            getline(ssLinha, coluna, '\t'); //primarytittle
            filme.setPrimaryTitle(coluna);

            getline(ssLinha, coluna, '\t'); //originaltittle
            filme.setOriginalTitle(coluna);

            getline(ssLinha, coluna, '\t'); //isadult
            if(isdigit(coluna[0]))
                filme.setIsAdult(stoi(coluna));
            else
                filme.setIsAdult(-1);

            getline(ssLinha, coluna, '\t'); //startYear
            if(isdigit(coluna[0]))
                filme.setStartYear(stoi(coluna));
            else
                filme.setStartYear(-1);

            getline(ssLinha, coluna, '\t'); //endYear
            if(isdigit(coluna[0]))
                filme.setEndYear(stoi(coluna));
            else
                filme.setEndYear(-1);

            getline(ssLinha, coluna, '\t'); //runtimeminutes
            if(isdigit(coluna[0]))
                filme.setRuntimeMinutes(stof(coluna));
            else
                filme.setRuntimeMinutes(-1);

            getline(ssLinha, coluna); //genres
            stringstream ssAux;
            string genero;
            ssAux.str(coluna);
            
            if(coluna.find(',') == string::npos){  //separação dos generos
                filme.setGenres(coluna);
            }
            else{
                while(getline(ssAux, genero, ',')){
                    filme.setGenres(genero);
                }
            }
        }
        ssLinha.clear();

        filmes[filme.getHash()].push_back(filme); //adiciona o filme na posição especificada pela hash
        i++;
    }

    filmesArq.close();

    //***********CINEMAS*********** 

    ifstream cinemasArq;
    vector<Cinema> cinemas;
    string linhaCinema;
    string colunaCinema;
    int idxCol = 0;  //indice para qual variável colunaCinema será direcioanado
    
    cinemasArq.open("dados/cinemas.txt");

    if(!cinemasArq.is_open()){
        std::cout << "NAO ABERTO" << endl;
    }
    
    //remover a primeira linhaCinema
    getline(cinemasArq, linhaCinema); 

    //Realiza a leitura de cinemas e extrais seus atributos
    while(getline(cinemasArq, linhaCinema)){
        Cinema cinema;
        stringstream sslinhaCinema(linhaCinema);

        while(getline(sslinhaCinema, colunaCinema, ',')){
            switch (idxCol){  //seta cada sub string em seu atributo no objeto cinema
            case 0: 
                cinema.setCinema_id(colunaCinema);
                break;
            case 1: 
                cinema.setNome(removeSpace(colunaCinema, 1));
                break;
            case 2: 
                cinema.setCord_x(stoi(removeSpace(colunaCinema, 1)));
                break;
            case 3: 
                cinema.setCord_y(stoi(removeSpace(colunaCinema, 1)));
                break;
            case 4: 
                cinema.setPreco(stof(removeSpace(colunaCinema, 1)));
                break;
            default:  //define as referencias de cada filme dentro de cinemas
                cinema.setFilmes_exibicao(Util::movieReference(stoi(removeSpace(colunaCinema, 3)), filmes));
                break;
            }
            idxCol++;
        }
        idxCol = 0;
        cinemas.push_back(cinema);  //adiciona o cinema ao vetor
    }

    cinemasArq.close();

    //***********FILTROS*********** 

    vector<Filme> filmesFiltro[HASH_CONST];


    vector<string> generosBusca = {""};
    string tiposBusca = "video";
    int anoSup = -2;
    int anoInf = -2;
    int duracaoSup = -2;
    int duracaoInf = -2;

    FiltroTeste::busca(filmes,filmesFiltro,tiposBusca,duracaoInf,duracaoSup,generosBusca,anoInf,anoSup);

    imprime(filmesFiltro);


    //termino da contagem do tempo do programa
    auto end = chrono::high_resolution_clock::now();
    // Calcular a duração da execução
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    // Imprimir o tempo de execução em milissegundos
    std::cout << "Tempo de execucao: " << duration.count() << " milissegundos" << endl;
}

void imprime(vector<Filme> (&filmes)[HASH_CONST]){
    for(vector<Filme> filmeHash : filmes){
        std::cout << endl;
        
        for(Filme filme : filmeHash){
            std::cout << filme.getTconst()<<" ";
            std::cout << filme.getTitleType()<<" ";
            std::cout << filme.getPrimaryTitle()<<" ";
            std::cout << filme.getOriginalTitle()<<" ";
            std::cout << filme.getIsAdult()<<" ";
            std::cout << filme.getStartYear()<<" ";
            std::cout << filme.getEndYear()<<" ";
            std::cout << filme.getRuntimeMinutes()<<" ";

            for(string genero: filme.getGenres()){
                std::cout << genero << " ";
            }

            std::cout << endl;
        }
    }
}

string removeSpace(string str, int quant){  // apaga o primeiro caracter (espaço em branco)
    str.erase(0, quant);
    return str;
}

