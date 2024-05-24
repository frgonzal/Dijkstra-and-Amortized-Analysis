#include "../headers/graph.hpp"
#include "../headers/queue/heap.hpp"
#include "../headers/queue/fibonacci.hpp"
#include "../headers/dijkstra.hpp"
#include <stdlib.h>
#include <iostream>
#include <float.h>
#include <vector>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ostream>
#include <unistd.h>
#include <vector>
#include <queue>
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
            if(!visited[v]){
                q.push(v);
            }
        }
    }

    for(int u = 0; u < visited.size(); u++){
        if(!visited[u]){
            std::cout << "Error en el grafo" << std::endl;
            exit(1);
        }

        for(auto [v, w] : g.edges[u]){
            if(v < 0 || v >= g.edges.size()){
                std::cout << "Error en el grafo" << std::endl;
                exit(1);
            }

            if(w <= 0 || w > 1){
                std::cout << "Error en el grafo" << std::endl;
                exit(1);
            }

            if(g.getWeight(u, v) != g.getWeight(v, u)){
                std::cout << "Error en el grafo" << std::endl;
                exit(1);
            }

            if(g.isConnectedTo(u, v) != g.isConnectedTo(v, u)){
                std::cout << "Error en el grafo" << std::endl;
                exit(1);
            }
        }


        for(int i=0; i<g.edges[u].size(); i++){
            for(int j=0; j<g.edges[u].size(); j++){
                auto [z1, w1] = g.edges[u][i];
                auto [z2, w2] = g.edges[u][j];
                if(z1 == z2 && i != j){
                    std::cout << "Error en el grafo" << std::endl;
                    exit(1);
                }
            }
        }
    }

    return;
}


void test_path(const Graph &g, const std::vector<int>& paths, const std::vector<double> &distances){


    for(int i = 0; i < paths.size(); i++){
        double dist = 0.0;
        int to = i;
        int from = paths[to];

        //std::cout << to << " <- ";
        while(from > -1){

            if(g.isConnectedTo(from, to)){
                dist += g.getWeight(from, to);
                std::cout << from << " - " << to << " (" << g.getWeight(from, to) << ") \n";
            } else {
                std::cout << "Error en la arista de " << from << " a " << to << std::endl;
                exit(1);
            }

            //std::cout << from;

            to = from;
            from = paths[to];
            //if(from > -1)
            //    std::cout << " <- ";
        }
        std::cout << std::endl;

        if(dist != distances[i]){
            std::cout << "Error en la distancia de " << i << " a la raiz" << std::endl;
            std::cout << "Distancia esperada: " << distances[i] << std::endl;
            std::cout << "Distancia obtenida: " << dist << std::endl;
            std::cout << g.getWeight(61, 83) << std::endl;

            exit(1);
        }
    }
}


int test_bin_heap(Graph &g){
    queue::Heap q = queue::Heap();

    auto start = std::chrono::high_resolution_clock::now();
    auto [paths, distances] = dijkstra(g, &q);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "time: " << elapsed.count() << "\n";

    test_path(g, paths, distances);
    return elapsed.count();
}

int test_fib_heap(Graph &g){
    queue::Fibonacci q =queue::Fibonacci();

    auto start = std::chrono::high_resolution_clock::now();
    auto [paths, distances] = dijkstra(g, &q);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "time: " << elapsed.count() << "\n";

    //test_path(g, paths, distances);
    return elapsed.count();
}

int main(){

    for(int i=10; i<=14; i+=2){
        for(int j=16; j<=22; j++){
            int v = (1 << i);
            int e = (1 << j);

            if(e > v*(v-1)/2) continue;
            std::cout << "\nTesting with 2^" << i << " vertices and 2^" << j << " edges" << std::endl;

            for(int k=0; k<50; k++){
                int seed = 123*i + 456*j + 789*k + 1;

                std::cout << "Graph " << k << std::endl;
                Graph g(v, e, seed);
                test_graph(g);
                //test_bin_heap(g);
                test_fib_heap(g);
            }

        }
    }



    return 0;
}