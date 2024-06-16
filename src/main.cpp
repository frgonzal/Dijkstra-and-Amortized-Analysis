#include <stdlib.h>
#include <iostream>
#include "../headers/queue/priqueue.hpp"
#include "../headers/queue/heap.hpp"
#include "../headers/queue/fibonacci.hpp"
#include "../headers/graph.hpp"
#include "../headers/dijkstra.hpp"



int main(){

    std::cout << "Creación de un grafo de 10 nodos y 50 aristas con pesos aleatorios entre 0 y 1. \n";
    Graph g(10, 50, 0);
    {
        std::cout << "Algoritmo de Dijkstra con cola de prioridad de Fibonacci. \n";
        queue::Fibonacci q = queue::Fibonacci();
        dijkstra(g, &q);
    }
    {
        std::cout << "Algoritmo de Dijkstra con cola de prioridad de Heap. \n";
        queue::Heap q = queue::Heap();
        dijkstra(g, &q);
    }


    return 0;
}