#include <fstream>
#include <map>
#include <iostream>
#include"Buscar.hpp"
#include"aho.hpp"

string leArquivo(string filePath);
map<char, vector<string>> verifyPattern(string text, map<char, vector<int>> patternIdx, map<char, vector<string>> patternsFound);
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

    patternIdx['@'];
    patternIdx['('];
    patternIdx['/'];
    
    for (auto& s : patterns)  // aho-korasick
        ahotrie.add_string(s);
    ahotrie.prepare();
    patternIdx = ahotrie.process(text, patternIdx);  // armazena os índices dos matches
    
    patternsFound = verifyPattern(text, patternIdx, patternsFound);
    imprimeMapa(patternIdx);
}

string leArquivo(string filePath){
    
    ifstream file(filePath);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());  // lê arquivo e converte para string
    return content;
}

map<char, vector<string>> verifyPattern(string text, map<char, vector<int>> patternIdx, map<char, vector<string>> patternsFound){

    for(const auto& par: patternIdx){
        switch (par.first){
        case '@':
            verifyEmail(par.second);  // retornar um map<char, vector<string>> (@: "alo@gmail.com", ...)
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

void imprimeMapa(map<char, vector<int>> patternIdx){
    
    for(const auto& par: patternIdx){
        cout << "Chave '" << par.first << "' : ";
        for(int idx: par.second)
            cout << idx << " ";
        cout << endl;
    }
}
