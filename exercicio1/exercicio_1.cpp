#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

#define MATRIZ_SIZE 9
#define MATRIZ_SIDE 3

typedef vector<vector<int>> Puzzle;

void print_matriz(Puzzle matriz)
{
    cout << "\n";
    for (int i = 0; i < MATRIZ_SIDE; i++)
    {
        for (int j = 0; j < MATRIZ_SIDE; j++)
        {
            cout << matriz[i][j] << " ";
            if ((j % 2) == 0 && (j != 0))
            {
                cout << "\n";
            }
        }
    }
}

vector<int> acoes(Puzzle estado)
{
    vector<int> x(MATRIZ_SIZE);
    int ix = 0;

    for (int i = 0; i < MATRIZ_SIDE; i++)
    {
        for (int j = 0; j < MATRIZ_SIDE; j++)
        {
            // MOVER NÓ i,j PARA CIMA OU ESQUERDA
            if (((i - 1) >= 0 && estado[i - 1][j] == 0) ||
                ((j - 1) >= 0 && estado[i][j - 1] == 0))
            {
                x[ix] = -1;
            }
            // MOVER NÓ i,j PARA BAIXO OU DIREITA
            else if (((i + 1) <= 2 && estado[i + 1][j] == 0) ||
                     ((j + 1) <= 2 && estado[i][j + 1] == 0))
            {
                x[ix] = 1;
            }
            else
            {
                x[ix] = 0;
            }
            ix++;
        }
    }

    return x;
}

bool goalState(Puzzle state)
{
    int value = 1;
    for (int i = 0; i < MATRIZ_SIDE; i++)
    {
        for (int j = 0; j < MATRIZ_SIDE; j++)
        {
            // Verifique se cada número está na posição correta
            if (i == 0 && j == 0)
            {
                // O primeiro espaço deve ser 0
                if (state[i][j] != 0)
                {
                    return false;
                }
            }
            else
            {
                if (state[i][j] != value)
                {
                    return false;
                }
                value++;
            }
        }
    }
    // Se todos os números estão na posição correta, então é o estado objetivo
    return true;
}

vector<Puzzle> getNeighbors(Puzzle state)
{
    vector<Puzzle> neighbors;
    int zero_i, zero_j;

    // Encontre a posição do 0 na matriz
    for (int i = 0; i < MATRIZ_SIDE; i++)
    {
        for (int j = 0; j < MATRIZ_SIDE; j++)
        {
            if (state[i][j] == 0)
            {
                zero_i = i;
                zero_j = j;
                break;
            }
        }
    }

    // Crie um vetor com as possíveis direções de movimento
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Para cada direção, verifique se o movimento é válido e, em caso afirmativo, adicione o novo estado à lista de vizinhos
    for (pair<int, int> dir : directions)
    {
        int new_i = zero_i + dir.first;
        int new_j = zero_j + dir.second;

        if (new_i >= 0 && new_i < MATRIZ_SIDE && new_j >= 0 && new_j < MATRIZ_SIDE)
        {
            Puzzle newState = state;
            swap(newState[zero_i][zero_j], newState[new_i][new_j]);
            neighbors.push_back(newState);
        }
    }

    return neighbors;
}

void bfs(Puzzle start)
{
    queue<Puzzle> q;
    set<Puzzle> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty())
    {
        Puzzle current = q.front();
        q.pop();

        if (goalState(current))
        {
            cout << "Solução encontrada!" << endl;
            print_matriz(current);
            return;
        }

        vector<Puzzle> neighbors = getNeighbors(current); // Função a ser implementada: retorna todos os estados que podem ser alcançados a partir do estado atual movendo o espaço vazio

        for (Puzzle neighbor : neighbors)
        {
            if (visited.find(neighbor) == visited.end())
            {
                q.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }

    cout << "Solução não encontrada" << endl;
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> matriz(MATRIZ_SIDE, vector<int>(3));
    // int matriz[3][3];
    //  7 2 4
    //  5 0 6
    //  8 3 1
    cout << "MATRIZ: \n"
         << endl;
    for (int i = 0; i < MATRIZ_SIDE; i++)
    {
        for (int j = 0; j < MATRIZ_SIDE; j++)
        {
            cin >> matriz[i][j];
        }
    }
    cout << "\n";
    bfs(matriz);
    cout << "\n";
    return 0;
}
