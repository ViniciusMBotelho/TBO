#include <iostream>
#include <fstream> // Para verificar a existência do arquivo
#include <algorithm>
#include <cairo/cairo.h>

using namespace std;

// Definindo a struct
typedef struct {
    string word;
    int quant;
} parStrInt;

class WordChart {
public:
    // Método estático para plotar o gráfico em PNG
    static void plotGraphPNG(const parStrInt* data, size_t size, const char* filename) {
        // Verificar se o arquivo já existe e removê-lo se necessário
        if (fileExists(filename)) {
            remove(filename);
            cout << "Arquivo existente removido.\n";
        }

        // Criar um contexto Cairo
        cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 600, 400);
        cairo_t* cr = cairo_create(surface);

        // Criar um vetor a partir do array estático
        vector<parStrInt> wordVector(data, data + size);

        // Ordenar os dados
        sort(wordVector.begin(), wordVector.end(), compareData);

        // Garantir que haja 10 palavras exibidas no gráfico
        int numWords = max(10, static_cast<int>(wordVector.size()));

        // Encontrar o número máximo de repetições para normalização
        int maxRepetitions = wordVector.front().quant;

        // Configurar margens e tamanhos
        const double marginX = 80;
        const double marginY = 50;
        const double barHeight = 30;
        const double barSpacing = 10;

        // Desenhar o gráfico
        for (int i = 0; i < numWords; ++i) {
            const auto& entry = (i < static_cast<int>(wordVector.size())) ? wordVector[i] : dummyData();
            double barWidth = 400.0 * entry.quant / maxRepetitions; // Normalizar para a largura da barra

            // Desenhar uma barra
            cairo_set_source_rgb(cr, 0.2, 0.4, 0.6); // Cor da barra (azul)
            cairo_rectangle(cr, marginX, marginY + i * (barHeight + barSpacing), barWidth, barHeight);
            cairo_fill(cr);

            // Escrever o nome da palavra dentro da barra (cor do texto: branco)
            cairo_set_source_rgb(cr, 1, 1, 1); // Cor do texto (branco)
            cairo_move_to(cr, marginX + barWidth + 10, marginY + i * (barHeight + barSpacing) + barHeight / 2);
            cairo_show_text(cr, entry.word.c_str());
        }

        // Salvar o resultado como um arquivo PNG
        cairo_surface_write_to_png(surface, filename);

        // Limpar
        cairo_destroy(cr);
        cairo_surface_destroy(surface);

        cout << "Gráfico salvo como '" << filename << "'\n";
    }

private:
    // Função de comparação para ordenação
    static bool compareData(const parStrInt& a, const parStrInt& b) {
        return a.quant > b.quant;
    }

    // Função para verificar a existência do arquivo
    static bool fileExists(const char* filename) {
        ifstream file(filename);
        return file.good();
    }

    // Função para criar dados fictícios para preencher o gráfico
    static parStrInt dummyData() {
        return {"", 0};
    }
};