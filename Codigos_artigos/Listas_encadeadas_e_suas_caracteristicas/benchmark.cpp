#include <iostream>
#include <vector>
#include <list>
#include <chrono>

void acessoAleatorio(int N) {
    const int ACESSOS = N/2;

    std::vector<int> v(N, 1);
    auto start_vec = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ACESSOS; ++i) {
        int r = rand() % N;
        int x = v[r]; // Acesso direto
    }
    auto end_vec = std::chrono::high_resolution_clock::now();
    auto duration_vec = std::chrono::duration_cast<std::chrono::milliseconds>(end_vec - start_vec);
    std::cout << "[Vetor] Tempo acesso aleatorio: " << duration_vec.count() << " ms" << std::endl;

    std::list<int> l(N, 1);
    auto start_list = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ACESSOS; ++i) {
        int r = rand() % N;
        auto it = l.begin();
        std::advance(it, r); // Acesso lento
        int x = *it;
    }
    auto end_list = std::chrono::high_resolution_clock::now();
    auto duration_list = std::chrono::duration_cast<std::chrono::milliseconds>(end_list - start_list);
    std::cout << "[Lista] Tempo acesso aleatorio: " << duration_list.count() << " ms" << std::endl;
}

void insercaoInicio(int N) {
    auto start_vec = std::chrono::high_resolution_clock::now();
    std::vector<int> v;
    for (int i = 0; i < N; ++i) {
        v.insert(v.begin(), i); // Ineficiente
    }
    auto end_vec = std::chrono::high_resolution_clock::now();
    auto duration_vec = std::chrono::duration_cast<std::chrono::milliseconds>(end_vec - start_vec);
    std::cout << "[Vetor] Tempo: " << duration_vec.count() << " ms" << std::endl;

    auto start_list = std::chrono::high_resolution_clock::now();
    std::list<int> l;
    for (int i = 0; i < N; ++i) {
        l.push_front(i); // Muito eficiente
    }
    auto end_list = std::chrono::high_resolution_clock::now();
    auto duration_list = std::chrono::duration_cast<std::chrono::milliseconds>(end_list - start_list);
    std::cout << "[Lista] Tempo: " << duration_list.count() << " ms" << std::endl;
}

int main() {
    const int TAM = 250000;
    std::cout << "[Cenario] Insercao no inicio" << std::endl;
    insercaoInicio(TAM);
    std::cout << "[Cenario] Acesso de um elemento aleatorio" << std::endl;
    acessoAleatorio(TAM);
    return 0;
}