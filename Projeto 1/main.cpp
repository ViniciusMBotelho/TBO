#include"Filtros.hpp"

using namespace std;

void imprimeFilmes(vector<Filme> (&filmes)[HASH_CONST]);
void imprimeCinemas(vector<Cinema> (&cinemas));
void escreveFilmes(vector<Filme> (&filmes)[HASH_CONST]);
void escreveCinemas(vector<Cinema> cinemas);
string removeSpace(string str, int quant);

int main(){
    //inicio da contagem do tempo do programa
    auto start = chrono::high_resolution_clock::now();
    
    //***********LEITURAS***********
    //***********FILMES*********** 
    vector<Filme> filmes[HASH_CONST];
    string coluna;
    string linha;
    stringstream ssLinha;
    ifstream filmesArq;

    filmesArq.open("dados/filmesCrop.txt");
    if(!filmesArq.is_open()){
        std::cout << "NAO ABERTO" << endl;
    }
    
    //remover a primeira linha
    getline(filmesArq, linha);
    linha.clear();

    auto startLeituraFilmes = chrono::high_resolution_clock::now();
    
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
    }
    
    auto endLeituraFilmes = chrono::high_resolution_clock::now();
    auto durationLeituraFilmes = chrono::duration_cast<chrono::milliseconds>(endLeituraFilmes - startLeituraFilmes);
    system("clear");
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
    linhaCinema.clear(); 

    auto startLeituraCienemas = chrono::high_resolution_clock::now();
    
    while(getline(cinemasArq, linhaCinema)){ //Realiza a leitura de cinemas e extrais seus atributos
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

    //***********MENU***********

    int opcaoMenu;
    do{
        cout << "Escolha qual tipo de busca:" << endl << endl << "1 - Filmes" << endl << "2 - Cinemas" << endl << endl << "Resposta: ";
        cin >> opcaoMenu;
        system("clear");

        switch (opcaoMenu){
        case 1:{
            vector<Filme> filmesFiltro[HASH_CONST];
            vector<string> generosBusca;
            string tiposBusca;
            int duraInf = -2;
            int duraSup = -2;
            int anoInf = -2;
            int anoSup = -2;
            generosBusca.clear();
            tiposBusca.clear();

            int resposta,quantGeneros;
            string generoAux;

            cout << "Deseja buscar por tipo? " << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;
            if (resposta != 2){
                cout << "Digite o tipo (tudo minúsculo): ";
                cin >> tiposBusca;
            }

            cout << "Deseja buscar por ano? " << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;
            if(resposta != 2){
                cout << "Informe o ano de inicio: ";
                cin >> anoInf;
                do{
                    cout << "Informe o ano de termino: ";
                    cin >> anoSup;
                    if(anoInf > anoSup) cout << "O ano de inicio nao pode ser maior que o ano de termino!";
                }while(anoInf > anoSup);
            }

            cout << "Deseja buscar por duração? " << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;
            if(resposta != 2){
                cout << "Informe o inicio do intervalo em minutos: ";
                cin >> duraInf;
                do{
                    cout << "Informe o termino em minutos: ";
                    cin >> duraSup;
                    if(duraInf > duraSup) cout << "O intervalo de inicio nao pode ser maior que o de termino!" << endl;
                }while(duraInf > duraSup);
            }

            cout << "Deseja buscar por genero? " << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;
            if (resposta != 2){
                cout << "Quantos generos deseja incluir no filtro? ";
                cin >> quantGeneros;
                cout << "Digite o genero (Primeira letra maiúscula): ";
                
                for (int i = 0; i < quantGeneros; i++){
                    cin >> generoAux;
                    generosBusca.push_back(generoAux);
                }  
            }
            
            auto startFiltroFilmes = chrono::high_resolution_clock::now();

            Filtros::buscaFilme(filmes, filmesFiltro, tiposBusca, duraInf, duraSup, generosBusca, anoInf, duraSup);

            auto endFiltroFilmes = chrono::high_resolution_clock::now();
            auto durationFiltroFilmes = chrono::duration_cast<chrono::milliseconds>(endFiltroFilmes - startFiltroFilmes);

            std::cout << "Tempo de filtro filmes: " << durationFiltroFilmes.count() << " milissegundos" << endl;

            cout << "Deseja salvar o resultado da busca?" << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;
            if(resposta==1) escreveFilmes(filmesFiltro);
            else imprimeFilmes(filmesFiltro);

            break;
        }
        
        case 2:{
            vector<Cinema> cinemasFiltro;
            vector<string> tiposBuscaCinema;
            vector<string> generosBuscaCinema;
            vector<int> limiteDuracoesCinema = {-2, -2};
            vector<int> limiteAnosCinema = {-2, -2};
            int distancia = -2;
            float preco = -2;
            tiposBuscaCinema.clear();
            generosBuscaCinema.clear();

            int resposta,quantAux;
            string stringAux;

            cout << "Deseja buscar cinemas com filmes por tipo específico? " << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;
            if (resposta != 2){
                cout << "Quantos tipos deseja incluir no filtro? ";
                cin >> quantAux;
                cout << "Digite o(s) tipo(s): ";
                
                for (int i = 0; i < quantAux; i++){
                    cin >> stringAux;
                    tiposBuscaCinema.push_back(stringAux);
                }  
            }

            cout << "Deseja buscar cinemas com filmes por genero específico? " << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;
            if (resposta != 2){
                cout << "Quantos generos deseja incluir no filtro? ";
                cin >> quantAux;
                cout << "Digite o genero (Primeira letra maiúscula): ";
                
                for (int i = 0; i < quantAux; i++){
                    cin >> stringAux;
                    generosBuscaCinema.push_back(stringAux);
                }  
            }

            cout << "Deseja buscar cinemas com filmes por duração específica? " << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;
            if(resposta != 2){
                cout << "Informe o inicio do intervalo em minutos: ";
                cin >> limiteDuracoesCinema[0];
                do{
                    cout << "Informe o termino em minutos: ";
                    cin >> limiteDuracoesCinema[1];
                    if(limiteDuracoesCinema[0] > limiteDuracoesCinema[1]) cout << "O intervalo de inicio nao pode ser maior que o de termino!" << endl;
                }while(limiteDuracoesCinema[0] > limiteDuracoesCinema[1]);
            }
            
            cout << "Deseja buscar cinemas por preço? " << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;
            if(resposta != 2){
                cout << "Informe o preco maximo: ";
                cin >> preco;
            }

            cout << "Deseja buscar cinemas por distância? " << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;
            if(resposta != 2){
                cout << "Informe a distância máxima: ";
                cin >> distancia;
            }

            auto startFiltroCinemas = chrono::high_resolution_clock::now();
            Filtros::buscaCinema(cinemas, cinemasFiltro, tiposBuscaCinema, generosBuscaCinema, limiteDuracoesCinema, distancia, preco, limiteAnosCinema);
            
            auto endFiltroCinemas = chrono::high_resolution_clock::now();
            auto durationFiltroCinemas = chrono::duration_cast<chrono::milliseconds>(endFiltroCinemas - startFiltroCinemas);
            std::cout << "Tempo de filtro cinemas: " << durationFiltroCinemas.count() << " milissegundos" << endl << endl;
            
            cout << "Deseja salvar o resultado da busca?" << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "resposta: ";
            cin >> resposta;

            if(resposta==1) 
                escreveCinemas(cinemasFiltro);
            else 
                imprimeCinemas(cinemasFiltro);

            break;
        }

        default:
            cout << endl << "Comando Invalido!" << endl << endl;
            continue;
        }

        cout << "Deseja fazer uma nova busca?" << endl << endl << "1 - Sim" << endl << "2 - Não" << endl << endl << "Resposta: ";
        cin >> opcaoMenu;
        if(opcaoMenu==2) opcaoMenu = 0;
        system("clear");
    }while(opcaoMenu!=0);

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

void escreveFilmes(vector<Filme> (&filmes)[HASH_CONST]){ //escreve o resultado da busca em um arquivo txt
     std::ofstream resultado("resultadoFilmes.txt", std::ofstream::trunc);

    if(!resultado.is_open()) 
        cout << "Nao aberto" << endl;

    for(vector<Filme> filmeHash : filmes){
        for(Filme filme : filmeHash){
            resultado << filme.getTitleType()<<" ";
            resultado << filme.getPrimaryTitle()<<" ";
            resultado << filme.getOriginalTitle()<<" ";
            resultado << filme.getIsAdult()<<" ";
            resultado << filme.getStartYear()<<" ";
            resultado << filme.getEndYear()<<" ";
            resultado << filme.getRuntimeMinutes()<<" ";

            for(string genero: filme.getGenres()){
                resultado << genero << " ";
            }
            resultado << "\n";
        }
    }
    cout << endl;
}

void escreveCinemas(vector<Cinema> cinemas){
    std::ofstream resultado("resultadoCinemas.txt", std::ofstream::trunc);

    if(!resultado.is_open()) 
        cout << "Nao aberto" << endl;

    for(Cinema cinema : cinemas){
        resultado << cinema.getCinema_id()<<" ";
        resultado << cinema.getNome()<<" ";
        resultado << cinema.getCord_x()<<" ";
        resultado << cinema.getCord_y()<<" ";
        resultado << cinema.getPreco()<<" ";

        for(Filme* filmeExibicao: cinema.getFilmes_exibicao()){
            if(filmeExibicao != nullptr)
                resultado << "tt" <<filmeExibicao->getTconst() << " ";
        }
        resultado << "\n";
    }
    
    cout << endl;
}

string removeSpace(string str, int quant){  // apaga o primeiro caracter (espaço em branco)
    str.erase(0, quant);
    return str;
}
