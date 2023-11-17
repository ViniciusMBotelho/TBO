#ifndef AHO_CORASICK_HEADER
#define AHO_CORASICK_HEADER

#include <queue>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

class Aho
{

    struct Vertex
    {
        unordered_map<char, int> children{};
        int parent = -1;
        int suffix_link = -1;
        int end_word_link = -1;
        int word_ID = -1;
        char parent_char;
        bool leaf = false;
    };

    vector<Vertex> trie;
    vector<int> words_length;
    int size;
    int root;
    int wordID;

public:
    Aho()
        : trie{}, words_length{}, size{0}, root{0}, wordID{0}
    {

        trie.push_back(Vertex{});
        ++size;
    }

    void add_string(const string &s)
    {
        int curVertex = root;

        for (char c : s)
        {

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

    void prepare()
    {
        queue<int> vertexQueue{};
        vertexQueue.push(root);

        while (!vertexQueue.empty())
        {
            int curVertex = vertexQueue.front();
            vertexQueue.pop();

            CalcSuffLink(curVertex);

            for (const auto &p : trie[curVertex].children)
                vertexQueue.push(trie[curVertex].children[p.first]);
        }
    }

    map<char, vector<int>> process(const string &text, map<char, vector<int>> patternIdx)
    {

        // vector<int> patternIdx;
        int currentState = root;
        int result = 0;

        for (int j = 0; j < text.size(); j++){

            while (true){

                if (trie[currentState].children.find(text[j]) != trie[currentState].children.end()){
                    currentState = trie[currentState].children[text[j]];
                    break;
                }

                if (currentState == root)
                    break;

                currentState = trie[currentState].suffix_link;
            }
            int checkState = currentState;

            while (true){

                checkState = trie[checkState].end_word_link;
                if (checkState == root)
                    break;

                result++;
                int indexOfMatch = j + 1 - words_length[trie[checkState].word_ID];

                switch (text[indexOfMatch]){
                case '@':
                    patternIdx['@'].push_back(indexOfMatch);
                    break;
                case '(':
                    patternIdx['('].push_back(indexOfMatch);
                    break;
                case '/':
                    patternIdx['/'].push_back(indexOfMatch);
                    break;
                }

                // cout << "There was a match at index " << indexOfMatch << ": ";
                // cout << text.substr(indexOfMatch, words_length[trie[checkState].word_ID]) << endl;

                checkState = trie[checkState].suffix_link;
            }
        }

        return patternIdx;
    }

private:
    void CalcSuffLink(int vertex){

        if (vertex == root){
            trie[vertex].suffix_link = root;
            trie[vertex].end_word_link = root;
            return;
        }

        if (trie[vertex].parent == root){
            trie[vertex].suffix_link = root;

            if (trie[vertex].leaf)
                trie[vertex].end_word_link = vertex;
            else
                trie[vertex].end_word_link = trie[trie[vertex].suffix_link].end_word_link;

            return;
        }

        int curBetterVertex = trie[trie[vertex].parent].suffix_link;
        char chVertex = trie[vertex].parent_char;

        while (true){

            if (trie[curBetterVertex].children.find(chVertex) != trie[curBetterVertex].children.end()){
                trie[vertex].suffix_link = trie[curBetterVertex].children[chVertex];
                break;
            }

            if (curBetterVertex == root){
                trie[vertex].suffix_link = root;
                break;
            }

            curBetterVertex = trie[curBetterVertex].suffix_link;
        }

        if (trie[vertex].leaf)
            trie[vertex].end_word_link = vertex;
        else
            trie[vertex].end_word_link = trie[trie[vertex].suffix_link].end_word_link;
    }
};

#endif