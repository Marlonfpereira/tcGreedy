#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

/* 
- ler arquivo
    - cria lista todos as entradas inicio
    - adiciona final

caso 1
- ordenar
- guloso lendo a lista incrementalmente

caso 2
- guloso procurando pelo menor inicio

 */

struct Aula {
    int inicio;
    int final;
};

vector<Aula> readFile(string filename) {
    vector<Aula> aulas;

    ifstream file(filename);
    int inicio, final;
    while (file >> inicio) {
        cout << inicio << " ";
        Aula aula;
        aula.inicio = inicio;
        aulas.push_back(aula);
    }
}

int main()
{
    readFile("data/Aula10.txt");
    return 0;
}
