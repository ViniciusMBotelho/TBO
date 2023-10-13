#include"Filtros.hpp"

using namespace std;

void imprimeFilmes(vector<Filme> (&filmes)[HASH_CONST]);
void imprimeCinemas(vector<Cinema> (&cinemas));

string removeSpace(string str, int quant);


// criar menu

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

    auto startLeituraFilmes = chrono::high_resolution_clock::now();
    //Realiza a leitura de filmes e extrais seus atributos
    while(getline(filmesArq, linha)){ //Realiza a leitura dos filmes e extrai seus atributos
        Filme filme;
        ssLinha.str(linha);

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
        ssLinha.clear();

        filmes[filme.getHash()].push_back(filme); //adiciona o filme na posição especificada pela hash
        i++;
    }
    
    auto endLeituraFilmes = chrono::high_resolution_clock::now();
    auto durationLeituraFilmes = chrono::duration_cast<chrono::milliseconds>(endLeituraFilmes - startLeituraFilmes);
    std::cout << "Tempo de leitura dos filmes: " << durationLeituraFilmes.count() << " milissegundos" << endl;


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


    auto startLeituraCienemas = chrono::high_resolution_clock::now();
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

    auto endLeituraCienemas = chrono::high_resolution_clock::now();
    auto durationLeituraCienemas = chrono::duration_cast<chrono::milliseconds>(endLeituraCienemas - startLeituraCienemas);
    std::cout << "Tempo de leitura dos cinemas: " << durationLeituraCienemas.count() << " milissegundos" << endl;

    cinemasArq.close();

    //***********FILTROS*********** 
    //***********FILMES*********** 
    vector<Filme> filmesFiltro[HASH_CONST];
    vector<string> generosBusca;
    // vector<int> limiteDuracoes = {-2,-2};  // nem faz sentido isso dar seg Fault
    // vector<int> limiteAnos = {2000, 2008};
    int duraInf = -2;
    int duraSup = -2;
    int anoInf = -2;
    int anoSup = 2018;
    generosBusca.clear();
    generosBusca = {"Reality-TV"};
    string tiposBusca = "tvEpisode";

    auto startFiltroFilmes = chrono::high_resolution_clock::now();

    Filtros::buscaFilme(filmes,filmesFiltro,tiposBusca,duraInf,duraSup,generosBusca, anoInf, anoSup);

    auto endFiltroFilmes = chrono::high_resolution_clock::now();
    auto durationFiltroFilmes = chrono::duration_cast<chrono::milliseconds>(endFiltroFilmes - startFiltroFilmes);
    std::cout << "Tempo de filtro filmes: " << durationFiltroFilmes.count() << " milissegundos" << endl;

    // imprimeFilmes(filmesFiltro);


    //***********CINEMA*********** 
    vector<Cinema> cinemasFiltro;
    vector<string> tiposBuscaCinema;
    vector<string> generosBuscaCinema;
    vector<int> limiteDuracoesCinema = {-2, -2};
    vector<int> limiteAnosCinema = {-2, -2};
    int distancia = -2;
    float preco = -2;
    tiposBuscaCinema.clear();
    generosBuscaCinema.clear();
    tiposBuscaCinema = {"tvEpisode"};
    generosBuscaCinema = {"Reality-TV"};
    
    auto startFiltroCinemas = chrono::high_resolution_clock::now();

    Filtros::buscaCinema(cinemas, cinemasFiltro, tiposBuscaCinema, generosBuscaCinema, limiteDuracoesCinema, distancia, preco, limiteAnosCinema);

    auto endFiltroCinemas = chrono::high_resolution_clock::now();
    auto durationFiltroCinemas = chrono::duration_cast<chrono::milliseconds>(endFiltroCinemas - startFiltroCinemas);
    std::cout << "Tempo de filtro cinemas: " << durationFiltroCinemas.count() << " milissegundos" << endl;

    // imprimeCinemas(cinemasFiltro);


    //termino da contagem do tempo do programa
    auto end = chrono::high_resolution_clock::now();
    // Calcular a duração da execução
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    // Imprimir o tempo de execução em milissegundos
    std::cout << "Tempo de execucao: " << duration.count() << " milissegundos" << endl;
}

void imprimeFilmes(vector<Filme> (&filmes)[HASH_CONST]){

    for(vector<Filme> filmeHash : filmes){
        for(Filme filme : filmeHash){
            std::cout << "tt" << filme.getTconst()<<" ";
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
    cout << endl;
}

void imprimeCinemas(vector<Cinema> (&cinemas)){

    for(Cinema cinema: cinemas){
        std::cout << cinema.getCinema_id()<<" ";
        std::cout << cinema.getNome()<<" ";
        std::cout << cinema.getCord_x()<<" ";
        std::cout << cinema.getCord_y()<<" ";
        std::cout << cinema.getPreco()<<" ";
        for(Filme* filmeExibicao: cinema.getFilmes_exibicao()){
            if(filmeExibicao != nullptr)
                std::cout << "tt"<<filmeExibicao->getTconst()<<" ";
        }
        std::cout<<endl;
    }
    cout << endl;
}

string removeSpace(string str, int quant){  // apaga o primeiro caracter (espaço em branco)
    str.erase(0, quant);
    return str;
}
