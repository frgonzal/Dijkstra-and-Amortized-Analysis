#include "../headers/graph.hpp"
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <iostream>
#include <float.h>



/** Constructor de la clase Graph.
*   Genera un grafo con aristas aleatorias.
*   @param v Cantidad de vértices del grafo.
*   @param e Cantidad de aristas del grafo.
Graph::Graph(int v, int e, int seed){
    if(v < 2 || e < v - 1 || e > v*(v-1)/2){
        std::cout << "No se puede generar un grafo con " << v << " vertices y " << e << " aristas\n";
        throw std::runtime_error("Error en los parametros del grafo");
    }

    srand(seed);
    edges.resize(v, std::vector<std::tuple<int, double>>());

    std::vector<std::tuple<int, int>> vertices;
    vertices.reserve(v*(v+1)/2);

    for(int i = 0; i < v; i++)
        for(int j = i+1; j < v; j++)
            vertices.emplace_back(i, j);

    for(int z = 1; z < v; z++){
        double weight = (((double)rand()+1)/((double)RAND_MAX+1));
        int u = rand() % z;
        int pos = u*(u-1)/2 + u*(v-u) + (z-u) - 1;

        if(u < 0 || u >= z)
            throw std::runtime_error("Error en el nodo");

        auto [a, b] = vertices[pos];
        if(a != u || b != z || pos < 0 || pos >= vertices.size())
            throw std::runtime_error("Error en la posición");

        connect(u, z, weight);
        swap(vertices[pos], vertices[z-1]);
    }
    
    std::shuffle(vertices.begin()+v, vertices.end(), std::default_random_engine(seed));

    for(int i=0; i<e-(v-1); i++){
        auto [u, z] = vertices[i+v];
        double weight = (((double)rand()+1)/((double)RAND_MAX+1));
        connect(u, z, weight);
    }
}
*/
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


/** Conecta 2 vertices en un grafo.
*   @param u Vértice origen.
*   @param v Vértice destino.
*   @param w Peso de la arista que conecta u y v.
*/
void Graph::connect(int u, int v, double w){
    if(u == v) 
        throw std::runtime_error("No se pueden conectar un nodo consigo mismo");

    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
}


/** Verifica si dos vertices están conectados.
*   @param u Vértice origen.
*   @param v Vértice destino.
*   @return true si u y v están conectados, false en caso contrario.
*/
bool Graph::isConnectedTo(int u, int v) const {
    for(auto [z, _] : edges[u])
        if(z == v) return true;

    return false;
}


/** Obtiene el peso de la arista que conecta 2 vertices.
*   @param u Vértice origen.
*   @param v Vértice destino.
*   @return Peso de la arista que conecta u y v.
*/
double Graph::getWeight(int u, int v) const {
    double weight = DBL_MAX;
    for(auto [z, w] : edges[u])
        if(z == v) 
            weight = std::min(weight, w);

    if (weight == DBL_MAX)
        throw std::runtime_error("No existe la arista");
    return weight;
}
