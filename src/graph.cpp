#include "../headers/graph.hpp"
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <iostream>
#include <float.h>


Graph::Graph(int v, int e, int seed){
    if(v < 2 || e < v - 1)
        throw std::runtime_error("Error en los parametros del grafo");

    srand(seed);
    edges.resize(v, std::vector<std::tuple<int, double>>());

    for(int z = 1; z < v; z++){
        double weight = (((double)rand()+1)/((double)RAND_MAX+1));
        int u = rand() % z;
        connect(u, z, weight);
    }
    

    for(int i=0; i<e-(v-1); i++){
        int u = rand() % v;
        int z;
        do{
            z = rand() % v;
        }while(z == u);

        double weight = (((double)rand()+1)/((double)RAND_MAX+1));
        connect(u, z, weight);
    }
}


void Graph::connect(int u, int v, double w){
    if(u == v) 
        throw std::runtime_error("No se pueden conectar un nodo consigo mismo");

    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
}


bool Graph::isConnectedTo(int u, int v) const {
    for(auto [z, _] : edges[u])
        if(z == v) return true;

    return false;
}


double Graph::getWeight(int u, int v) const {
    double weight = DBL_MAX;
    for(auto [z, w] : edges[u])
        if(z == v) 
            weight = std::min(weight, w);

    if (weight == DBL_MAX)
        throw std::runtime_error("No existe la arista");
    return weight;
}
