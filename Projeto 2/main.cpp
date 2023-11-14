#include"Buscar.hpp"

int main() {

    // string text = "ABABDABACDABABCABAB";
    // string pattern = "AB";

    // vector<int> idx_patterns = Buscar::KMP_mult(text, pattern);

    // for(int idx: idx_patterns)
    //     cout << "idx: " << idx << '\n';

    string arr[] = {"he", "she", "hers", "his"};
    string text = "ahishershe alo1234567@gmail.com.br as dasb";
    int k = sizeof(arr)/sizeof(arr[0]);

    Buscar::buscaPalavras(arr, k, text);
 
    return 0;
}
