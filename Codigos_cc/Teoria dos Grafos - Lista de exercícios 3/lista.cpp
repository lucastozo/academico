// Questao 1
#include <vector>
bool digrafoSimetrico(std::vector<std::vector<int>> matriz)
{
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz.size(); j++) {
            if (matriz[i][j] != matriz[j][i]) {
                return false;
            }
        }
    }
    return true;
}

// Questao 2
#include <iostream>
#include <vector>
void grauDeTodosVertices(std::vector<std::vector<int>> G)
{
    std::vector<int> graus(G.size(), 0);
    for (int v = 0; v < G.size(); v++) {
        for (int i = 0; i < G.size(); i++) {
            if (G[v][i] == 1) {
                graus[v]++;
            }   
        }
    }
    bool grafoRegular = true;
    bool grafoCompleto = true;
    for (int i = 0; i < graus.size(); i++) {
        std::cout << "Grau do vértice " << i << ": " << graus[i] << std::endl;
        if (i < graus.size() && graus[i] != graus[i+1]) grafoRegular = false;
        if (graus[i] != graus.size() - 1) grafoCompleto = false;
    }
    if (grafoRegular) std::cout << "O grafo é regular" << std::endl;
    else std::cout << "O grafo não é regular" << std::endl;

    if (grafoCompleto) std::cout << "O grafo é completo" << std::endl;
    else std::cout << "O grafo não é completo" << std::endl;
}

// Questao 3
#include <iostream>
#include <vector>
void grauEntradaSaida(std::vector<std::vector<int>> G)
{
    std::vector<int> grausEntrada(G.size(), 0);
    std::vector<int> grausSaida(G.size(), 0);
    for (int v = 0; v < G.size(); v++) {
        for (int i = 0; i < G.size(); i++) {
            if (G[i][v] == 1) grausEntrada[v]++;
            if (G[v][i] == 1) grausSaida[v]++;
        }
    }

    for (int i = 0; i < G.size(); i++) {
        std::cout << "Grau de entrada do vértice " << i << ": " << grausEntrada[i] << std::endl;
        std::cout << "Grau de saída do vértice " << i << ": " << grausSaida[i] << std::endl;
    }
}

// Questao 4
#include <iostream>
#include <vector>
void removerAresta(std::vector<std::vector<int>> &G, int v, int w)
{
    if (G[v][w] == 0) {
        std::cout << "A aresta " << v << "-" << w << " não existe" << std::endl;
        return;
    }
    G[v][w] = 0;
}

// Questao 5
#include <vector>
std::vector<std::vector<int>> complemento(std::vector<std::vector<int>> G)
{
    std::vector<std::vector<int>> complemento(G.size(), std::vector<int>(G.size()));
    for (int v = 0; v < G.size(); v++) {
        for (int w = 0; w < G.size(); w++) {
            if (v != w && G[v][w] == 0) complemento[v][w] = 1;
        }   
    }
    return complemento;
}

// Questao 6
#include <vector>
class Aresta {
public:
    int origem, destino;
};
std::vector<std::vector<int>> matrizAdjacencia(std::vector<Aresta> arestas)
{
    int maxVertice = 0;
    for (int i = 0; i < arestas.size(); i++) {
        if (arestas[i].origem > maxVertice) {
            maxVertice = arestas[i].origem;
        }
        if (arestas[i].destino > maxVertice) {
            maxVertice = arestas[i].destino;
        }
    }

    int numVertices = maxVertice + 1;
    std::vector<std::vector<int>> matriz(numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < arestas.size(); i++) {
        matriz[arestas[i].origem][arestas[i].destino] = 1;
        matriz[arestas[i].destino][arestas[i].origem] = 1;
    }
    
    return matriz;
}