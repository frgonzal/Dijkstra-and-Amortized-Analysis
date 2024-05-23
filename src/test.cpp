#include "../headers/graph.hpp"
#include "../headers/queue/queue.hpp"
#include "../headers/queue/heap.hpp"
#include "../headers/queue/fibonacci.hpp"
#include "../headers/dijkstra.hpp"
#include <stdlib.h>
#include <iostream>
#include <float.h>
#include <memory>
#include <vector>


void test_path(const Graph &g, const std::vector<int>& paths, const std::vector<double> &distances){
    for(int i = 0; i < paths.size(); i++){
        double dist = 0.0;
        int to = i;
        int from = paths[to];

        std::cout << to << " <- ";
        while(from > -1){

            if(g.isConnectedTo(from, to)){
                dist += g.getWeight(from, to);
            } else {
                std::cout << "Error en la arista de " << from << " a " << to << std::endl;
                exit(1);
            }

            std::cout << from;

            to = from;
            from = paths[to];
            if(from > -1)
                std::cout << " <- ";
        }
        std::cout << std::endl;

        if(dist != distances[i]){
            std::cout << "Error en la distancia de " << i << " a la raiz" << std::endl;
            exit(1);
        }
    }
}


int main(){
    Graph g((1<<8), (1<<10));

    //std::unique_ptr<Queue> heap_q = std::make_unique<queue::Heap>(queue::Heap());
    std::unique_ptr<Queue> fibo_q = std::make_unique<queue::Fibonacci>(queue::Fibonacci());

    // do not use until implemented
    auto [paths, distances] = dijkstra(g, fibo_q);
    test_path(g, paths, distances);
    //for(int i=0; i<paths.size(); i++){
    //    std::cout << "Nodo: " << i << " Distancia: " << distances[i] << " Padre: " << paths[i] << std::endl;
    //}

    //fibo_q->heapify(10);
    return 0;
}