#include <chrono>
#include <random>
#include <fstream>
#include <boost/random.hpp>
#include <string>

using namespace std;

void generate_tests(int n, int m, string file_name);

int main(int argc, char *argv[])
{
    int min_categories = 1;
    int max_categories = 20;
    int min_movies = 0;
    int max_movies = 25000;
    int total = (max_categories - min_categories) * (max_movies - min_movies) / 50;

    for (int i = min_movies; i <= max_movies; i += 50)
    {
        for (int j = min_categories; j < max_categories; j++)
        {
            string file_name = "./input/input_" + to_string(i) + '_' + to_string(j) + ".txt";
            generate_tests(i, j, file_name);
            total--;
            if (total % 1000 == 0)
                cout << total << endl;
        }
    }
    cout << total << endl;

    return 0;
}

void generate_tests(int n, int m, string file_name)
{
    ofstream inputFile;
    // inputFile.open("./test/input2.txt");
    inputFile.open(file_name);
    inputFile << n << " " << m << endl;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    // Definindo distribuição normal com média de 3 e desvio padrão de 1
    normal_distribution<double> distribution_dif(3, 1.0);

    uniform_int_distribution<int> distribution_hr(0, 23);
    uniform_int_distribution<int> distribution_cat(1, m);

    vector<int> maxFilmes(m); // Vetor para armazenar o máximo de filmes por categoria
    for (int i = 0; i < m; i++)
    {
        maxFilmes[i] = distribution_cat(generator); // Gerando o máximo de filmes para cada categoria
        inputFile << maxFilmes[i] << " ";           // Escrevendo o valor no arquivo de entrada
    }
    inputFile << endl;

    for (int i = 0; i < n; i++)
    {
        int hora_inicio = distribution_hr(generator);
        double dif_media = distribution_dif(generator);
        int hora_fim = ((int)hora_inicio + (int)round(dif_media)) % 24;
        int categoria = distribution_cat(generator);

        inputFile << hora_inicio << " " << hora_fim << " " << categoria << endl;
    }

    inputFile.close();
    return;
}