#include <fstream>
#include <map>
#include <iostream>
#include <cctype>
#include <cwctype>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include"Buscar.hpp"
#include"aho.hpp"

typedef struct {
    string word;
    int quant;
}parStrInt;

string fileReader(string filePath);
void verifyPattern(string text, map<char, vector<int>> patternIdx, map<char, vector<string>> &patternsFound);
void verifyEmail(string text, vector<int> idxs, map<char, vector<string>> &patternsFound);
void verifyPhone(string text, vector<int> idxs, map<char, vector<string>> &patternsFound);
void verifyDate(string text, vector<int> idxs, map<char, vector<string>> &patternsFound);
bool isNumeric(const string& str);
void textClassifier(string filePath, map<string, int> &wordCounter);
int colorFunc(int max, int num);
void quick(parStrInt wordCounter[], int esq, int dir);

int main() {

    // KMP e KMP_mult

    // string text = "ABABDABACDABABCABAB";
    // string pattern = "AB";
    // vector<int> idx_patterns = Buscar::KMP_mult(text, pattern);
    // for(int idx: idx_patterns)
    //     cout << "idx: " << idx << '\n';


    // DATA MINING
    
    Aho ahotrie {};
    string filePath = "dados/emails.txt";
    string text = fileReader(filePath);  // le o arquivo e joga para uma string
    vector<string> patterns {"@", "(", "/"};  // email patterns para buscar
    map<char, vector<int>> patternIdx;  // indice dos padrões
    map<char, vector<string>> patternsFound;  // padrões encontrados no texto

    // patternIdx['@'] = {};
    // patternIdx['('] = {};
    // patternIdx['/'] = {};

    // for (auto& s : patterns)  // aho-korasick
    //     ahotrie.add_string(s);
    // ahotrie.prepare();
    // patternIdx = ahotrie.process(text, patternIdx);  // armazena os índices dos matches
    
    // verifyPattern(text, patternIdx, patternsFound);
    // for(const auto& par: patternsFound){  // imprime dados encontrados
    //     cout << "Chave '" << par.first << "' : ";
    //     for(string idx: par.second)
    //         cout << idx << " | ";
    //     cout << endl;
    // }

    // VISUALIZAÇÂO DE DADOS

    map<string, int> wordCounter;
    int i=0;
    
    textClassifier(filePath, wordCounter);
    auto maxElement = std::max_element(wordCounter.begin(), wordCounter.end(), [](const auto& p1, const auto& p2) {  // maior elemento do map
        return p1.second < p2.second;});

    parStrInt wordCounterArr[wordCounter.size()];
    for(const auto& par: wordCounter){  // passa o map para array (string, int) * necessário para fazer a ordenação
        wordCounterArr[i].word = par.first;
        wordCounterArr[i].quant = par.second;
        i++;
    }

    cout << "Total de palavras válidas: " << wordCounter.size() << endl;
    quick(wordCounterArr, 0, wordCounter.size()-1);  // ordena o array
    for(i=0; i < 10; i++){  // imprime relação palavra : quantidade
        if(wordCounterArr[i].quant < 3) continue;
        cout << "Chave '" << "\x1b[38;2;" << colorFunc(maxElement->second, wordCounterArr[i].quant) << ";0;0m" << wordCounterArr[i].word << "\x1b[0m" << "' : " << wordCounterArr[i].quant;
        cout << endl;
    }

}

/*Abri um arquivo de texto e retorna em formato de string*/
string fileReader(string filePath){
    
    ifstream file(filePath);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());  // lê arquivo e converte para string
    return content;
}

/*Chama as funções de verificação de padrões específica de cada tipo de informação*/
void verifyPattern(string text, map<char, vector<int>> patternIdx, map<char, vector<string>> &patternsFound){

    patternsFound['@'] = {};
    patternsFound['('] = {};
    patternsFound['/'] = {};

    for(auto& par: patternIdx){
        switch (par.first){
        case '@':
            verifyEmail(text, par.second, patternsFound);
            break;
        case '(':
            verifyPhone(text, par.second, patternsFound);
            break;
        case '/':
            verifyDate(text, par.second, patternsFound);
            break;
        }
    }
}

/*Realiza a verificação se email atende os requesitos*/
void verifyEmail(string text, vector<int> idxs, map<char, vector<string>> &patternsFound){
    /* 
        exemple@mail.com
        1) buscar 15 caracteres para trás: tem que ter um espaço do segundo ao décimo-quinto char para passar; (exemple)
        2) buscar 10 caracteres para frente: tem que encontrar um ponto e sem espaço; (mail)
        3) buscar .com ou .com.br e um espaço no final;  (.com / .com.br)
        4) substring idxInicial - idxFianl e colocar em patternsFound
    */
   
    string emailPiece;  // string auxiliar

    if (!idxs.empty()) {
        bool confirmation = true;
        for(int idx: idxs){ 
            
            confirmation = true;

            if(text.substr((idx-14), 14).find_last_of(" ") == 13 || text.substr((idx-14), 14).find_last_of(" ") == string::npos){  // verifica credencial do email
                confirmation = false;
                continue;
            }
            string candidato = text.substr((idx-14), 14);
            emailPiece = candidato.substr(candidato.find_last_of(" ") + 1, idx - candidato.find_last_of(" "));  // adiciona a string

            if(text.substr((idx), 10).find_first_of(".") == string::npos || 
            (text.substr((idx), 10).find_first_of(' ') != string::npos || !isalpha(text[idx+1]))){  // verifica dominio
                confirmation = false;
                continue;     
            }
            candidato = text.substr(idx, 10);
            emailPiece.append(candidato.substr(0, candidato.find_first_of(".")));  // adiciona a string
            
            int domain = text.substr((idx), 10).find_first_of(".") - 1;
            if((text.substr((idx+domain+2), 4) != "com " && text.substr((idx+domain+2), 7) != "com.br ")){  // verifica final
                confirmation = false;
                continue;
            }
            if(text.substr((idx+domain+2), 4) == "com ")  // adiciona a string
                emailPiece.append(".com");
            else if (text.substr((idx+domain+2), 7) == "com.br ")
                emailPiece.append(".com.br");

            if(confirmation)  // passou nos testes
                patternsFound['@'].push_back(emailPiece);
        }
    }
}

/*Realiza a verificação se telefone atende os requesitos*/
void verifyPhone(string text, vector<int> idxs, map<char, vector<string>> &patternsFound){

    /*
    (38) 12345-6789
    1) Verifica a parte do DDD (38)
    2) Verifica a primeira parte do número (12345)
    3) Verifica a segunda parte do número (6789)
    */

    if(!idxs.empty()){
        bool confirmation = true;
        for(int idx: idxs){

            confirmation = true;
            if(!isNumeric(text.substr(idx+1, 2))){  // Primeira parte
                confirmation = false;
                continue;
            }
            if(text.substr(idx+3, 2) != ") "){
                confirmation = false;
                continue;
            }
            if(!isNumeric(text.substr(idx+5, 5))){  // Segunda parte
                confirmation = false;
                continue;
            }
            if(text[idx+10] != '-'){
                confirmation = false;
                continue;
            }
            if(!isNumeric(text.substr(idx+11, 4)) || isdigit(text[idx+15])){  // Final
                confirmation = false;
                continue;
            }

            if(confirmation)  // passou nos testes
                patternsFound['('].push_back(text.substr(idx, 15));
        }
    }
}

/*Realiza a verificação se data atende os requesitos*/
void verifyDate(string text, vector<int> idxs, map<char, vector<string>> &patternsFound){

    /*
    23/02/1999
    1) Verifica primeira parte (23)
    2) Verifica segunda parte (02)
    3) Verifica terceira parte (1999)
    */

    if(!idxs.empty()){
        bool confirmation = true;
        for(int idx: idxs){

            confirmation = true;

            if(!isNumeric(text.substr(idx-2,2))){
                confirmation = false;
                continue;
            }

            if(stoi(text.substr(idx-2,2)) > 31){
                confirmation = false;
                continue;
            }

            if(!isNumeric(text.substr(idx+1,2))){
                confirmation = false;
                continue;
            }
            
            if(stoi(text.substr(idx+1,2)) > 12){
                confirmation = false;
                continue;
            }

            if(!isNumeric(text.substr(idx+4,4))) {
                confirmation = false;
                continue;
            }

            if(isblank(text[idx+8] == 0) || text[idx+8] == '\n'){
                confirmation = false;
                continue;
            }

            if(confirmation)  // passou nos testes
                patternsFound['/'].push_back(text.substr(idx-2, 10));
        }
    }
}

/*Verificação se string é apenas numérica*/
bool isNumeric(const string& str) {
    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

/*Faz a contagem de palavras encontradas em um texto*/
void textClassifier(string pathFile, map<string, int> &wordCounter){

    ifstream file;
    vector<string> textWords;
    string word;
    string exceptDict = {"nos com das lhe tão dos são ele está esta este que por para têm tem uma que umas uns mais pode como ser suas seu sua não sim cada"};  // palavras ignoradas

    file.open(pathFile);
    while(file >> word){
        word[0] = tolower(word[0]);
        if(word.size() < 3) continue;

        if(!isalnum(word.back())) 
            word.pop_back();  // último caractere não alfa-numérico

        if(!isalnum(word.at(0)))
            word.erase(0,1);  // primeiro caractere não alfa-numérico
        
        if(Buscar::KMP(exceptDict, word) != -1) continue;  // verifica se está em exceptDict

        if(wordCounter.find(word) == wordCounter.end())  // palavra nova
            wordCounter[word] = 1;
        else  // palavra já encontrada antes
            wordCounter[word]++; 
    }
}

/*Relaciona um valor numérico ao intervalo [0-255]
O menor valor para 0 e o maior para 255*/
int colorFunc(int max, int num){
    return (num/(float)max) * 255;
}

/*Ordena o array de struct que contem o par chave-valor das palavras contadas por quick-sort*/
void quick(parStrInt wordCounter[], int esq, int dir) {
    int pivo = esq, i, j;
    parStrInt ch;

    for (i = esq + 1; i <= dir; i++) {
        j = i;
        if (wordCounter[j].quant > wordCounter[pivo].quant) {
            ch = wordCounter[j];
            while (j > pivo) {
                wordCounter[j] = wordCounter[j - 1];
                j--;
            }
            wordCounter[j] = ch;
            pivo++;
        }
    }

    if (pivo - 1 >= esq)
        quick(wordCounter, esq, pivo - 1);

    if (pivo + 1 <= dir)
        quick(wordCounter, pivo + 1, dir);
}

