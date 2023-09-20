#include<vector>
#include<string>
#include "Filmes.hpp"

using namespace std;

class cinemas{
    private:
        string cinema_id;
        string nome;
        int cord_x;
        int cord_y;
        float preco;
        vector<string> filmes_exibicao;
};
