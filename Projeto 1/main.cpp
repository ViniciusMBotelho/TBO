#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

int main(){
    ifstream cinemas;
    cinemas.open("dados/cinemas.txt");
    
    if(cinemas.is_open())
        cout << "b";
    else
        cout << "!!!";
    getchar();
    string linha;
    while(!cinemas.eof()){
        // getline(cinemas, linha);
        // cout << linha << endl;
        // cout << "a";
    }
}