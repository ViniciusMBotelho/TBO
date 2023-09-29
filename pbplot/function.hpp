#include<iostream>
#include<vector>
#include"./plPlot_Includes/pbPlots.hpp"
#include"./plPlot_Includes/supportLib.hpp"

using namespace std;

//*************************************************IMPRIMET**************************************************************

void imprime(vector<int> vec){
  for(long unsigned int i=0; i<vec.size(); i++)
      cout << vec[i] << " ";
    cout << endl;
}

//**********************************************INSERTION SORT***********************************************************

double insertionSort(vector<int> vec, int tam, bool aleatorio){
    
    double comp = 0;
    int i, valor, j;
    for (i = 1; i < tam; i++) {
        valor = vec[i];
        j = i - 1;
        while (j >= 0 && vec[j] > valor) {
            comp+=2;
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = valor;
        comp++;
        if(!aleatorio)
            imprime(vec);  // imprime repetidamente
    }
    comp = comp + (tam-1);
    if(aleatorio)  // imprime uma só vez
        imprime(vec);
    cout << "Comparações: " << comp << endl << "--------------------------------------------------------------" << endl;
    return comp;
}

//**********************************************SELECTION SORT***********************************************************

double selectionSort(vector<int> vec, int tam, bool aleatorio){

    double comp = 0;
    int idx = 0;
    for(int i=0; i<tam; i++){
        idx = i;
        for(int j=i+1; j<tam; j++){
            if(vec[idx] > vec[j])
                idx = j;   
        }
        // swap
        int aux = vec[i];
        vec[i] = vec[idx];
        vec[idx] = aux;
        
        comp += (tam-i-1);  // acessos
        if(!aleatorio)
            imprime(vec);  // imprime repetidamente
    }
    if(aleatorio)  // imprime uma só vez
        imprime(vec);
    cout << "Comparações: " << comp << endl << "--------------------------------------------------------------" << endl;
    return comp;
}

//**********************************************GERA ALEATORIA***********************************************************


vector<double> criaAleatoria(bool opcao){
    
    vector<double> vetorteste(100);
    vector<int> vAle;
    int k=0;

    if(opcao==true){

        for(int i=1; i<=100; i++){
            for(int j=1; j<=i; j++){
                vAle.push_back((rand() % 20) + 1);
            }
            imprime(vAle);
            vetorteste[k++] = selectionSort(vAle, vAle.size(), true);
            vAle.clear();
        }
    }else{

        for(int i=1; i<=100; i++){
            for(int j=1; j<=i; j++){
                vAle.push_back((rand() % 20) + 1);
            }
            imprime(vAle);
            vetorteste[k++] = insertionSort(vAle, vAle.size(), true);
            vAle.clear();
        }
    }
    return vetorteste;
}

int criaPNG(vector<double> vetorteste, bool opcao){
    bool success;
    vector<double> vetor100(100);

    // Preencher o vetor com valores de 1 a 99
    for (int i = 0; i < 100; i++) {
        vetor100[i] = i + 1;
    }

    StringReference *errorMessage = new StringReference();
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	success = DrawScatterPlot(imageReference, 1500, 1200, &vetor100, &vetorteste, errorMessage);

    if(success){
        vector<double> *pngdata = ConvertToPNG(imageReference->image);
        if(opcao == true) 
            WriteToFile(pngdata, "./images/insertion.png");
        else
            WriteToFile(pngdata, "./images/selection.png");
        DeleteImage(imageReference->image);
	}else{
	    cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            wcerr << c;
        }
        cerr << endl;
	}

	return success ? 0 : 1;
}