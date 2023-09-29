#include<vector>
#include<string>
#include "Filme.hpp"

using namespace std;

class Cinema{
    private:
        string cinema_id;
        string nome;
        int cord_x;
        int cord_y;
        float preco;
        vector<string> filmes_exibicao;

    public:

        void limpaFilmes(){
            filmes_exibicao.clear();
        }

        string getCinema_id()
        {
            return cinema_id;
        }
        void setCinema_id(string cinema_id1)
        {
            cinema_id = cinema_id1;
        }
        string getNome()
        {
            return nome;
        }
        void setNome(string nome1)
        {
            nome = nome1;
        }
        int getCord_x()
        {
            return cord_x;
        }
        void setCord_x(int cord_x1)
        {
            cord_x = cord_x1;
        }
        int getCord_y()
        {
            return cord_y;
        }
        void setCord_y(int cord_y1)
        {
            cord_y = cord_y1;
        }
        float getPreco()
        {
            return preco;
        }
        void setPreco(float preco1)
        {
            preco = preco1;
        }
        vector<string> getFilmes_exibicao()
        {
            return filmes_exibicao;
        }
        void setFilmes_exibicao(string filmes_exibicao1)
        {
            filmes_exibicao.push_back(filmes_exibicao1);
        }

    public:
        
};

