#include <queue>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

class Aho
{
    // Estrutura que representa um nó da Trie
    struct Vertex
    {
        unordered_map<char, int> children{}; // Mapeia caracteres para índices dos filhos
        int parent = -1;                      // Índice do pai
        int suffix_link = -1;                 // Link de sufixo
        int end_word_link = -1;               // Link de fim de palavra
        int word_ID = -1;                     // Identificador único da palavra
        char parent_char;                     // Caractere do pai
        bool leaf = false;                    // Indica se é uma folha
    };

    // Vetor que representa a Trie
    vector<Vertex> trie;
    vector<int> words_length; // Armazena o comprimento de cada palavra
    int size;                 // Número de nós na Trie
    int root;                 // Índice do nó raiz
    int wordID;               // Identificador único para cada palavra

public:
    // Construtor da classe
    Aho()
        : trie{}, words_length{}, size{0}, root{0}, wordID{0}
    {
        trie.push_back(Vertex{}); // Inicializa a Trie com um nó raiz
        ++size;
    }

    // Adiciona uma string à Trie
    void add_string(const string &s)
    {
        int curVertex = root;

        for (char c : s)
        {
            // Adiciona um novo nó se o caractere ainda não estiver presente
            if (trie[curVertex].children.find(c) == trie[curVertex].children.end())
            {
                trie.push_back(Vertex{});
                trie[size].parent = curVertex;
                trie[size].parent_char = c;
                trie[curVertex].children[c] = size;
                size++;
            }

            curVertex = trie[curVertex].children[c];
        }

        trie[curVertex].leaf = true;
        trie[curVertex].word_ID = wordID;
        words_length.push_back(s.size());

        ++wordID;
    }

    // Prepara a Trie calculando os links de sufixo
    void prepare()
    {
        queue<int> vertexQueue{};
        vertexQueue.push(root);

        while (!vertexQueue.empty())
        {
            int curVertex = vertexQueue.front();
            vertexQueue.pop();

            CalcSuffLink(curVertex);

            // Adiciona os filhos à fila para processamento
            for (const auto &p : trie[curVertex].children)
                vertexQueue.push(trie[curVertex].children[p.first]);
        }
    }

    // Procura padrões em um texto e retorna os índices das ocorrências
    map<char, vector<int>> process(const string &text, map<char, vector<int>> patternIdx)
    {
        int currentState = root;

        for (int j = 0; j < text.size(); j++)
        {
            while (true)
            {
                // Transição de estado com base no caractere atual do texto
                if (trie[currentState].children.find(text[j]) != trie[currentState].children.end())
                {
                    currentState = trie[currentState].children[text[j]];
                    break;
                }

                // Se não houver transição, segue o link de sufixo
                if (currentState == root)
                    break;

                currentState = trie[currentState].suffix_link;
            }
            int checkState = currentState;

            while (true)
            {
                // Siga o link de fim de palavra e registre as ocorrências
                checkState = trie[checkState].end_word_link;
                if (checkState == root)
                    break;

                // Incrementa o contador de ocorrências e registra o índice
                patternIdx[text[j]].push_back(j);

                checkState = trie[checkState].suffix_link;
            }
        }

        return patternIdx;
    }

private:
    // Calcula os links de sufixo e de fim de palavra para um nó na Trie
    void CalcSuffLink(int vertex)
    {
        if (vertex == root)
        {
            trie[vertex].suffix_link = root;
            trie[vertex].end_word_link = root;
            return;
        }

        if (trie[vertex].parent == root)
        {
            trie[vertex].suffix_link = root;

            // Se for uma folha, o link de fim de palavra é o próprio nó
            if (trie[vertex].leaf)
                trie[vertex].end_word_link = vertex;
            else
                trie[vertex].end_word_link = trie[trie[vertex].suffix_link].end_word_link;

            return;
        }

        int curBetterVertex = trie[trie[vertex].parent].suffix_link;
        char chVertex = trie[vertex].parent_char;

        while (true)
        {
            // Encontrar um nó com um filho correspondente ao caractere do nó atual
            if (trie[curBetterVertex].children.find(chVertex) != trie[curBetterVertex].children.end())
            {
                trie[vertex].suffix_link = trie[curBetterVertex].children[chVertex];
                break;
            }

            // Se não encontrar, segue o link de sufixo
            if (curBetterVertex == root)
            {
                trie[vertex].suffix_link = root;
                break;
            }

            curBetterVertex = trie[curBetterVertex].suffix_link;
        }

        // Atualiza o link de fim de palavra
        if (trie[vertex].leaf)
            trie[vertex].end_word_link = vertex;
        else
            trie[vertex].end_word_link = trie[trie[vertex].suffix_link].end_word_link;
    }
};