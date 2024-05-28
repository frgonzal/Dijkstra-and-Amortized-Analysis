#include "../headers/graph.hpp"
#include "../headers/queue/heap.hpp"
#include "../headers/queue/fibonacci.hpp"
#include "../headers/dijkstra.hpp"
#include <stdlib.h>
#include <iostream>
#include <float.h>
#include <tuple>
#include <vector>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ostream>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <chrono>




void test_graph(const Graph &g){    
    std::vector<bool> visited(g.edges.size(), false);
    std::queue <int> q;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        visited[u] = true;
        for(auto [v, w] : g.edges[u]){
            if(!visited[v])
                q.push(v);
        }
    }

    for(int u = 0; u < visited.size(); u++){
        if(!visited[u])
            throw std::runtime_error("No conexo");

        for(auto [v, w] : g.edges[u]){
            if(v < 0 || v >= g.edges.size())
                throw std::runtime_error("Nodo fuera de rango");

            if(w <= 0 || w > 1)
                throw std::runtime_error("Pesos fuera de rango");

            if(g.getWeight(u, v) != g.getWeight(v, u))
                throw std::runtime_error("Pesos no simetricos");

            if(g.isConnectedTo(u, v) != g.isConnectedTo(v, u))
                throw std::runtime_error("Aristas no simetricas");
        }

        for(int i=0; i<g.edges[u].size(); i++){
            for(int j=0; j<g.edges[u].size(); j++){
                auto [z1, w1] = g.edges[u][i];
                auto [z2, w2] = g.edges[u][j];
                if(z1 == z2 && i != j)
                    throw std::runtime_error("Arista repetida");
            }
        }
    }
}



void test_path(const Graph &g, const std::vector<int>& paths, const std::vector<double> &distances){
    for(int i = 0; i < paths.size(); i++){
        double dist = 0.0;
        int to = i;
        int from = paths[to];

        while(from > -1){

            if(g.isConnectedTo(from, to))
                dist += g.getWeight(from, to);
            else 
                throw std::runtime_error("Error en la arista");

            to = from;
            from = paths[to];
        }

        if(dist != distances[i]){
            std::cout << "Error en la distancia de " << i << " a la raiz" << std::endl;
            std::cout << "Distancia esperada: " << distances[i] << std::endl;
            std::cout << "Distancia obtenida: " << dist << std::endl;
            std::cout << g.getWeight(61, 83) << std::endl;
            throw std::runtime_error("Error en la distancia");
        }
    }
}


template <typename T>
void test_vectores(const std::vector<T>& v1, const std::vector<T>& v2){
    if(v1.size() != v2.size())
        throw std::runtime_error("Tamaño de los vectores diferentes");

    for(int i = 0; i < v1.size(); i++){
        if(v1[i] != v2[i])
            throw std::runtime_error("Elementos diferentes");
    }
}


std::tuple<std::vector<int>, std::vector<double>> test_bin_heap(Graph &g){
    queue::Heap q = queue::Heap();

    auto start = std::chrono::high_resolution_clock::now();
    auto [paths, distances] = dijkstra(g, &q);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Bin Heap time: " << elapsed.count() << "\n";

    return std::make_tuple(paths, distances);
}

std::tuple<std::vector<int>, std::vector<double>> test_fib_heap(Graph &g){
    queue::Fibonacci q =queue::Fibonacci();

    auto start = std::chrono::high_resolution_clock::now();
    auto [paths, distances] = dijkstra(g, &q);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Fib Heap time: " << elapsed.count() << "\n";

    return std::make_tuple(paths, distances);
}


void test(int i, int j, int v, int e, int seed){
    std::cout << "====  TEST : " << i << " " << j << "  ====\n";

    auto start = std::chrono::high_resolution_clock::now();
    Graph g(v, e, seed);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Graph creation time: " << elapsed.count() << "\n";

    //test_graph(g);
    auto [p1, d1] = test_bin_heap(g);
    auto [p2, d2] = test_fib_heap(g);
    test_vectores<int>(p1, p2);
    test_vectores<double>(d1, d2);
}

int main(){
    for(int i=10; i<=14; i+=2){
        for(int j=16; j<=22; j++){
            for(int k=0; k<50; k++){
                int v = 1<<i, e = 1<<j, seed = i*12345 + j*6789;
                if(v > 1 && e >= v - 1 && e <= v*(v-1)/2)
                    test(i, j, v, e, seed);
            }
        }
    }
    return 0;
}