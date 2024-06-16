#include "../headers/graph.hpp"
#include "../headers/queue/heap.hpp"
#include "../headers/queue/fibonacci.hpp"
#include "../headers/dijkstra.hpp"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <float.h>
#include <tuple>
#include <vector>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ostream>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <ostream>



/** Verifica si un grafo es conexo, 
 *  si los nodos están en el rango correcto,
 *  si los pesos de las aristas están en el rango correcto
 *  y si las aristas son simétricas.
 *  
 *  @param g Grafo a verificar.
 */
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

            if(g.isConnectedTo(u, v) &&  !g.isConnectedTo(v, u))
                throw std::runtime_error("Aristas no simetricas");
        }
    }
}


/**  Verifica que las distancias de los caminos más cortos sean correctas.
 * 
 *   @param g Grafo con pesos positivos en sus aristas.
 *   @param paths Vector con los padres de cada nodo en el árbol de caminos más cortos.
 *   @param distances Vector con las distancias de cada nodo a la raíz.
 */
void test_path(const Graph &g, const std::vector<int>& paths, const std::vector<double> &distances){
    for(int i = 0; i < paths.size(); i++){
        double dist = 0.0;
        int to = i;
        int from = paths[to];

        while(from > -1){
            dist += g.getWeight(from, to);
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


/**  Verifica que los vectores sean iguales.
 * 
 *   @param v1 Vector 1.
 *   @param v2 Vector 2.
 */
template <typename T>
void test_vectores(const std::vector<T>& v1, const std::vector<T>& v2){
    if(v1.size() != v2.size())
        throw std::runtime_error("Tamaño de los vectores diferentes");

    for(int i = 0; i < v1.size(); i++){
        if(v1[i] != v2[i])
            throw std::runtime_error("Elementos diferentes");
    }
}


/**  Guarda los resultados de los experimentos en un archivo csv.
 * 
 *   @param times Vector con los tiempos de ejecución de los algoritmos.
 */
void save_results(const std::vector<std::tuple<int,int,double,std::string>> &times){
    std::ofstream outFile("results/results.csv", std::ios::app);

    for(auto [i, j, t, type] : times)
        outFile << i << "," << j << "," << t << "," << type << "\n";

    outFile.close();
}


/**  Calcula los caminos más cortos de un grafo utilizando el algoritmo de Dijkstra.
 * 
 *   @tparam T Tipo de la estructura que permite obtener y eliminar el par con menor distancia.
 * 
 *   @param g Grafo con pesos positivos en sus aristas.
 *   @return Tupla con los caminos más cortos, las distancias y el tiempo de ejecución.
 */
template <typename T>
std::tuple<std::vector<int>, std::vector<double>, double> test_priqueue(const Graph &g){
    T q = T();

    auto start = std::chrono::high_resolution_clock::now();
    auto [paths, distances] = dijkstra(g, &q);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    return std::make_tuple(std::move(paths), std::move(distances), elapsed.count());
}


/**  Realiza un experimento con un grafo.
 * 
 *   @param i Exponente de la cantidad de vértices.
 *   @param j Exponente de la cantidad de aristas.
 */
void test(int i, int j){
    std::vector<std::tuple<int, int, double, std::string>> results;
    for(int k=1; k<=100; k++){
        int v = 1<<i, e = 1<<j, seed = i*j*k*123 + 543253;

        std::cout << "k: " << k << " v: " << v << " e: " << e << std::endl;

        /* Crear grafo */
        auto start = std::chrono::high_resolution_clock::now();
        const Graph g(v, e, seed);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Graph creation time: " << elapsed.count() << "\n";

        /* Realizar experimento con Colas de Fibonacci */
        queue::Fibonacci fib = queue::Fibonacci();
        auto [p2, d2, t_fib]  = test_priqueue<queue::Fibonacci>(g);
        std::cout << "Fib Heap time: " << t_fib << "\n";
        results.emplace_back(i, j, t_fib, "FibHeap");

        /* Realizar experimento con Heap */
        queue::Heap heap = queue::Heap();
        auto [p1, d1, t_heap] = test_priqueue<queue::Heap>(g);
        std::cout << "Bin Heap time: " << t_heap << "\n";
        results.emplace_back(i, j, t_heap, "BinHeap");

        /* Verificar resultados */
        test_graph(g);
        test_path(g, p1, d1);
        test_vectores<int>(p1, p2);
        test_vectores<double>(d1, d2);
    }
    //save_results(results);
}

int main(){
    for(int j=16; j<=27; j++){
        for(int i=10; i<=14; i+=2){
            std::cout << "====  TEST : " << i << " " << j << "  ====\n";
            test(i, j);
        }
    }
    return 0;
}