#include <fstream>
#include <map>
#include <iostream>
#include <cctype>
#include"Buscar.hpp"
#include"aho.hpp"

string leArquivo(string filePath);
map<char, vector<string>> verifyPattern(string text, map<char, vector<int>> patternIdx, map<char, vector<string>> &patternsFound);
void verifyEmail(string text, vector<int> idxs, map<char, vector<string>> &patternsFound);
void imprimeMapa(map<char, vector<int>> patternIdx);

int main() {

    // KMP e KMP_mult OK

    // string text = "ABABDABACDABABCABAB";
    // string pattern = "AB";
    // vector<int> idx_patterns = Buscar::KMP_mult(text, pattern);
    // for(int idx: idx_patterns)
    //     cout << "idx: " << idx << '\n';



    

    Aho ahotrie {};
    string text = leArquivo("dados/emails.txt");  // le o arquivo e joga para uma string
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
    // imprimeMapa(patternIdx);
}

string leArquivo(string filePath){
    
    ifstream file(filePath);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());  // lê arquivo e converte para string
    return content;
}

map<char, vector<string>> verifyPattern(string text, map<char, vector<int>> patternIdx, map<char, vector<string>> &patternsFound){

    for(auto& par: patternIdx){
        switch (par.first){
        case '@':
            verifyEmail(text, par.second, patternsFound);  // retornar (referência) um map<char, vector<string>> (@: "alo@gmail.com", ...)
            break;
        case '(':
            // verifyPhone();
            break;
        case '/':
            // verifyDate();
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
    
    int idxIni, idxFin;
    //gabr ielRamos @gmail.com
    if (!idxs.empty()) {
        bool confirmation = true;
        for(int idx: idxs){  
            if(text.substr((idx-14), 14).find_last_of(' ') == 13){  // verifica credencial do email
                confirmation = false;
                continue;
            }
            cout << "!" <<text.substr((idx-14), 14) << endl;

            if(text.substr((idx), 10).find_first_of(".") == string::npos || 
            (text.substr((idx), 10).find_first_of(' ') != string::npos || !isalpha(text[idx+1]))){ // verifica dominio
                confirmation = false;
                continue;     
            }
            
            int domain = text.substr((idx), 10).find_first_of(".") - 1;
            if((text.substr((idx+domain+2), 4) != "com " && text.substr((idx+domain+2), 7) != "com.br ")){ //verifica final
                confirmation = false;
                continue;
            }
            
            idxIni = text.substr((idx-14), 14).find_last_of(" ") + 1;
            // cout << text.substr((idx-14), 14) << endl;
            // cout << idxIni << " minh chibata menina" << endl;

            
        }

        if(confirmation){

        }
    }
}

void imprimeMapa(map<char, vector<int>> patternIdx){
    
    for(const auto& par: patternIdx){
        cout << "Chave '" << par.first << "' : ";
        for(int idx: par.second)
            cout << idx << " ";
        cout << endl;
    }
}
