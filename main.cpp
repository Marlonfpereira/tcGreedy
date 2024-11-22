#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string.h>

using namespace std;

/*
- ler arquivo ✅
    - cria lista todos as entradas inicio
    - adiciona final

caso 1
- ordenar
- guloso lendo a lista incrementalmente

caso 2
- guloso procurando pelo menor inicio

 */

struct Aula
{
    int inicio = INT32_MAX;
    int final = INT32_MAX;
    bool alocada = false;
};

void printAulas(vector<Aula> aulas)
{
    for (int i = 0; i < aulas.size(); i++)
    {
        cout << aulas[i].inicio << " " << aulas[i].final << endl;
    }
    cout << "------------\n";
}

vector<Aula> readFile(string filename)
{
    vector<Aula> aulas;

    ifstream file(filename);
    string lineInicio, lineFinal;
    getline(file, lineInicio);
    getline(file, lineFinal);

    char *inicios = strtok((char *)lineInicio.c_str(), " ");
    while (inicios != NULL && isdigit(inicios[0]))
    {
        Aula aula;
        aula.inicio = atoi(inicios);
        aulas.push_back(aula);

        inicios = strtok(NULL, " ");
    }

    char *finais = strtok((char *)lineFinal.c_str(), " ");
    for (int i = 0; i < aulas.size(); i++)
    {
        aulas[i].final = atoi(finais);
        finais = strtok(NULL, " ");
    }

    return aulas;
}

vector<Aula> ordenaAulas(vector<Aula> aulas)
{
    qsort(&aulas[0], aulas.size(), sizeof(Aula), [](const void *a, const void *b)
          {
        Aula *aulaA = (Aula *)a;
        Aula *aulaB = (Aula *)b;

        return (aulaA->inicio - aulaB->inicio); });
    return aulas;
}

int procuraMenorInicio(vector<Aula> aulas)
{
    Aula menorAula;
    int menorAulaI;
    for (int i = 0; i < aulas.size(); i++)
        if (aulas[i].inicio < menorAula.inicio && !aulas[i].alocada)
        {
            menorAula = aulas[i];
            menorAulaI = i;
        }

    return menorAulaI;
}

vector<vector<Aula>> Greedy(vector<Aula> aulas, bool ordena)
{
    vector<vector<Aula>> salas;
    salas.push_back(vector<Aula>());

    if (ordena)
        aulas = ordenaAulas(aulas);

    for (int i = 0; i < aulas.size(); i++)
    {
        int menorAula = ordena ? i : procuraMenorInicio(aulas);

        for (int j = 0; j < salas.size(); j++)
        {
            if (salas[j].size() == 0 || (salas[j].back().final <= aulas[menorAula].inicio))
            {
                salas[j].push_back(aulas[menorAula]);
                aulas[menorAula].alocada = true;
                break;
            }
        }

        if (!aulas[menorAula].alocada)
        {
            salas.push_back(vector<Aula>());
            salas.back().push_back(aulas[menorAula]);
            aulas[menorAula].alocada = true;
        }
    }

    return salas;
}

int main(int argc, char *argv[])
{
    string filename = "data/Aula10.txt";
    bool ordena = true;
    if (argc == 2)
        filename = argv[1];

    if (argc == 3)
        ordena = atoi(argv[2]);

    vector<Aula> aulas = readFile(filename);

    vector<vector<Aula>> salas = Greedy(aulas, ordena);
    cout << salas.size() << endl;
    return 0;
}