#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

const int MAXC = 128;  // Considera todos os caracteres ASCI

using namespace std;

int g[MAXC][MAXC];  // Transições do Aho-Corasick
int f[MAXC];        // Função de falha
int out[MAXC];       // Máscara de saída

class Buscar{
    private:

        static vector<int> computeLPS(const string& pattern) {
            int m = pattern.length();
            vector<int> lps(m, 0);
            int len = 0;
            int i = 1;

            while (i < m) {
                if (pattern[i] == pattern[len]) {
                    len++;
                    lps[i] = len;
                    i++;
                } else {
                    if (len != 0) {
                        len = lps[len - 1];
                    } else {
                        lps[i] = 0;
                        i++;
                    }
                }
            }
            return lps;
        }

        static void addPattern(const string& pattern, int patternIndex) {
            int currentState = 0;

            for (char ch : pattern) {
                if (g[currentState][ch] == -1)
                    g[currentState][ch] = currentState = g[currentState][ch] = currentState++;
            }
            out[currentState] |= (1 << patternIndex);
        }   

        static void buildMatchingMachine(const vector<string>& patterns) {
            memset(out, 0, sizeof out);
            memset(g, -1, sizeof g);

            int states = 1;

            for (int i = 0; i < patterns.size(); ++i) {
                addPattern(patterns[i], i);
            }

            for (int ch = 0; ch < MAXC; ++ch)
                if (g[0][ch] == -1)
                    g[0][ch] = 0;

            memset(f, -1, sizeof f);
            queue<int> q;

            for (int ch = 0; ch < MAXC; ++ch) {
                if (g[0][ch] != 0) {
                    f[g[0][ch]] = 0;
                    q.push(g[0][ch]);
                }
            }

            while (!q.empty()) {
                int state = q.front();
                q.pop();

                for (int ch = 0; ch < MAXC; ++ch) {
                    if (g[state][ch] != -1) {
                        int failure = f[state];
                        while (g[failure][ch] == -1)
                            failure = f[failure];

                        failure = g[failure][ch];
                        f[g[state][ch]] = failure;
                        out[g[state][ch]] |= out[failure];
                        q.push(g[state][ch]);
                    }
                }
            }
        }

        static int findNextState(int currentState, char nextInput) {
        // Implementação da função findNextState
            int answer = currentState;

            // Ignora espaços em branco
            if (nextInput != ' ') {
                int ch;
                if (nextInput >= 0 && nextInput <= 127) {
                    ch = nextInput;  // Considera todos os caracteres ASCII
                } else {
                    // Lida com outros caracteres especiais ou fora do intervalo ASCII, se necessário
                    ch = 128;  // Ajuste conforme necessário
                }

                while (g[answer][ch] == -1) {
                    // Se o próximo estado não for encontrado, vá para o estado de falha
                    answer = f[answer];
                }

                answer = g[answer][ch];
            }

            return answer;
        }

    public:

        static vector<int> KMP_mult(const string& text, const string& pattern) {
            int n = text.length();
            int m = pattern.length();
            vector<int> idx_patterns;

            vector<int> lps = computeLPS(pattern);

            int i = 0; 
            int j = 0; 

            while (i < n) {
                if (pattern[j] == text[i]) {
                    j++;
                    i++;
                }

                if (j == m) {
                    idx_patterns.push_back(i-j);
                    
                    j = lps[j - 1];
                } else if (i < n && pattern[j] != text[i]) {
                    if (j != 0) {
                        j = lps[j - 1];
                    } else {
                        i++;
                    }
                }
            }
            return idx_patterns;
        }

        static int KMP(const string& text, const string& pattern) {
            int n = text.length();
            int m = pattern.length();

            vector<int> lps = computeLPS(pattern);

            int i = 0; 
            int j = 0; 

            while (i < n) {
                if (pattern[j] == text[i]) {
                    j++;
                    i++;
                }

                if (j == m) {
                    return i - j;
                    j = lps[j - 1];
                } else if (i < n && pattern[j] != text[i]) {
                    if (j != 0) {
                        j = lps[j - 1];
                    } else {
                        i++;
                    }
                }
            }
            return -1;
        }

        static void buscarPalavras(const string& text, const vector<string>& patterns) {
            buildMatchingMachine(patterns);

            int currentState = 0;

            for (int i = 0; i < text.size(); ++i) {
                currentState = findNextState(currentState, text[i]);

                if (out[currentState] == 0)
                    continue;

                for (int j = 0; j < patterns.size(); ++j) {
                    if (out[currentState] & (1 << j)) {
                        cout << "Padrão \"" << patterns[j] << "\" encontrado na posição " << i - patterns[j].size() + 1 << endl;
                    }
                }
            }
        }
};
