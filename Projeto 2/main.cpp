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

    // KMP e KMP_mult OK

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
    map<char, vector<string>> patternsFound;  // padrões encontrados na string

    patternIdx['@'] = {};
    patternIdx['('] = {};
    patternIdx['/'] = {};

    for (auto& s : patterns)  // aho-korasick
        ahotrie.add_string(s);
    ahotrie.prepare();
    patternIdx = ahotrie.process(text, patternIdx);  // armazena os índices dos matches
    
    verifyPattern(text, patternIdx, patternsFound);
    for(const auto& par: patternsFound){  // imprime dados encontrados
        cout << "Chave '" << par.first << "' : ";
        for(string idx: par.second)
            cout << idx << " | ";
        cout << endl;
    }

    // VISUALIZAÇÂO DE DADOS

    map<string, int> wordCounter;
    int i=0;
    
    textClassifier(filePath, wordCounter);
    auto maxElement = std::max_element(wordCounter.begin(), wordCounter.end(), [](const auto& p1, const auto& p2) {  // maior elemento do map
        return p1.second < p2.second;});

    parStrInt wordCounterArr[wordCounter.size()];
    for(const auto& par: wordCounter){  // map para array (string, int)
        wordCounterArr[i].word = par.first;
        wordCounterArr[i].quant = par.second;
        i++;
    }

    quick(wordCounterArr, 0, wordCounter.size()-1);  // ordena o array
    for(i=0; i<wordCounter.size(); i++){  // imprime relação palavra : quantidade
        if(wordCounterArr[i].quant < 3) continue;
        cout << "Chave '" << "\x1b[38;2;" << colorFunc(maxElement->second, wordCounterArr[i].quant) << ";0;0m" << wordCounterArr[i].word << "\x1b[0m" << "' : " << wordCounterArr[i].quant;
        cout << endl;
    }
}


string fileReader(string filePath){
    
    ifstream file(filePath);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());  // lê arquivo e converte para string
    return content;
}

void verifyPattern(string text, map<char, vector<int>> patternIdx, map<char, vector<string>> &patternsFound){

    patternsFound['@'] = {};
    patternsFound['('] = {};
    patternsFound['/'] = {};

    for(auto& par: patternIdx){
        switch (par.first){
        case '@':
            verifyEmail(text, par.second, patternsFound);  // retornar (referência) um map<char, vector<string>> (@: "alo@gmail.com", ...)
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

void verifyEmail(string text, vector<int> idxs, map<char, vector<string>> &patternsFound){
    /* 
        1) buscar 15 caracteres para trás: tem que ter um espaço do segundo ao décimo-quinto char para passar; (pegar o idxInicial)
        2) buscar 10 caracteres para frente: tem que encontrar um ponto e sem espaço;
        3) buscar .com ou .com.br e um espaço no final;  (pegar o idxFinal)
        4) substring idxInicial - idxFianl e colocar em patternsFound
    */
   
    string emailPiece;

    if (!idxs.empty()) {
        bool confirmation = true;
        for(int idx: idxs){ 
            
            confirmation = true;

            // se possível trocar o tamanho pré '@' e tranformar inteiros em const
            if(text.substr((idx-14), 14).find_last_of(" ") == 13 || text.substr((idx-14), 14).find_last_of(" ") == string::npos){  // verifica credencial do email
                confirmation = false;
                continue;
            }
            string candidato = text.substr((idx-14), 14);
            emailPiece = candidato.substr(candidato.find_last_of(" ") + 1, idx - candidato.find_last_of(" "));  // adiciona a string

            if(text.substr((idx), 10).find_first_of(".") == string::npos || 
            (text.substr((idx), 10).find_first_of(' ') != string::npos || !isalpha(text[idx+1]))){ // verifica dominio
                confirmation = false;
                continue;     
            }
            candidato = text.substr(idx, 10);
            emailPiece.append(candidato.substr(0, candidato.find_first_of(".")));  // adiciona a string
            
            int domain = text.substr((idx), 10).find_first_of(".") - 1;
            if((text.substr((idx+domain+2), 4) != "com " && text.substr((idx+domain+2), 7) != "com.br ")){ //verifica final
                confirmation = false;
                continue;
            }
            if(text.substr((idx+domain+2), 4) == "com ")  // adiciona a string
                emailPiece.append(".com");
            else if (text.substr((idx+domain+2), 7) == "com.br ")
                emailPiece.append(".com.br");

            if(confirmation)
                patternsFound['@'].push_back(emailPiece);
        }
    }
}

void verifyPhone(string text, vector<int> idxs, map<char, vector<string>> &patternsFound){

    if(!idxs.empty()){
        bool confirmation = true;
        for(int idx: idxs){

            confirmation = true;
            if(!isNumeric(text.substr(idx+1, 2))){
                confirmation = false;
                continue;
            }
            if(text.substr(idx+3, 2) != ") "){
                confirmation = false;
                continue;
            }
                
            if(!isNumeric(text.substr(idx+5, 5))){
                confirmation = false;
                continue;
            }

            if(text[idx+10] != '-'){
                confirmation = false;
                continue;
            }

            if(!isNumeric(text.substr(idx+11, 4)) || isdigit(text[idx+15])){
                confirmation = false;
                continue;
            }

            if(confirmation)
                patternsFound['('].push_back(text.substr(idx, 15));
        }
    }
}

void verifyDate(string text, vector<int> idxs, map<char, vector<string>> &patternsFound){
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

            if(confirmation){
                patternsFound['/'].push_back(text.substr(idx-2, 10));
                continue;
            }      
        }
    }
}

bool isNumeric(const string& str) {
    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

void textClassifier(string pathFile, map<string, int> &wordCounter){

    ifstream file;
    vector<string> textWords;
    string word;
    string exceptDict = {"com das dos são que por para têm tem uma que umas uns mais pode como ser suas seu sua não sim cada"};

    file.open(pathFile);
    while(file >> word){
        word[0] = tolower(word[0]);
        if(!isalpha(word.back()))
            word.pop_back();

        if(!isalpha(word.at(0)))
            word.erase(0,1);
        
        if((word.length() < 3) || (Buscar::KMP(exceptDict, word) != -1)) continue;

        if(wordCounter.find(word) == wordCounter.end()){
            wordCounter[word] = 1;
            // cout << word << ' ';
        }
        
        else{
            wordCounter[word]++;
            // cout << word << ' ';
        }
    }
}

int colorFunc(int max, int num){
    return (num/(float)max) * 255;
}

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

