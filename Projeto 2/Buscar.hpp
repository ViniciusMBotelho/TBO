#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAXS = 500;
const int MAXC = 26;
int out[MAXS];
int f[MAXS];
int g[MAXS][MAXC];

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

        static int buildMatchingMachine(string arr[], int k)
        {
            memset(out, 0, sizeof out);
            memset(g, -1, sizeof g);

            int states = 1;

            for (int i = 0; i < k; ++i)
            {
                const string &word = arr[i];
                int currentState = 0;

                for (int j = 0; j < word.size(); ++j)
                {
                    int ch = word[j] - 'a';

                    if (g[currentState][ch] == -1)
                        g[currentState][ch] = states++;

                    currentState = g[currentState][ch];
                }
                out[currentState] |= (1 << i);
            }

            for (int ch = 0; ch < MAXC; ++ch)
                if (g[0][ch] == -1)
                    g[0][ch] = 0;

            memset(f, -1, sizeof f);
            queue<int> q;

            for (int ch = 0; ch < MAXC; ++ch)
            {
                if (g[0][ch] != 0)
                {
                    f[g[0][ch]] = 0;
                    q.push(g[0][ch]);
                }
            }
            while (q.size())
            {
                int state = q.front();
                q.pop();
                for (int ch = 0; ch <= MAXC; ++ch)
                {
                    if (g[state][ch] != -1)
                    {
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

            return states;
        }

        static int findNextState(int currentState, char nextInput)
        {
            int answer = currentState;
            int ch = nextInput - 'a';

            while (g[answer][ch] == -1)
                answer = f[answer];
            return g[answer][ch];
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

        static void buscaPalavras(string arr[], int k, string text){

            vector<int> idxs;

            buildMatchingMachine(arr, k);
            int currentState = 0;

            for (int i = 0; i < text.size(); ++i)
            {
                currentState = findNextState(currentState, text[i]);
                if (out[currentState] == 0)
                    continue;
                for (int j = 0; j < k; ++j)
                {
                    if (out[currentState] & (1 << j))
                    {
                        cout << "Palavra " << arr[j] << " appears from " << i - arr[j].size() + 1 << "to " << i << endl;
                    }
                }
            }
        }
};
