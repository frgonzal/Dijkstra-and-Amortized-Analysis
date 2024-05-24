#include "../headers/graph.hpp"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <random>



/** Constructor de la clase Graph.
*   Genera un grafo con aristas aleatorias.
*   @param v Cantidad de vértices del grafo.
*   @param e Cantidad de aristas del grafo.
*/
Graph::Graph(int v, int e, int seed){
    if(v < 2 || e < v - 1 || e > v*(v-1)/2){
        printf("No se puede generar un grafo con %d vértices y %d aristas\n", v, e);
        exit(10);
    }

    srand(seed);
    edges.resize(v, std::vector<std::tuple<int, double>>());


    for(int i = 1; i < v; i++){

        /** w in (0, 1] */
        double weight = (((double)rand()+1)/((double)RAND_MAX+1));

        /** u in [1,..., i-1] */
        int u = (i > 1)? rand()%(i-1) + 1 : 0;

        connect(u, i, weight);
    }

    std::vector<std::tuple<int, int>> vertices;
    vertices.reserve(v*(v-1)/2 - (v-1));

    for(int i = 0; i < v; i++)
        for(int j = i+1; j < v; j++)
            vertices.push_back(std::make_tuple(i, j));
    
    std::shuffle(vertices.begin(), vertices.end(), std::default_random_engine(seed));

    for(int i=0; i<e-(v-1); i++){
        auto [u, v] = vertices[i];
        double weight = (((double)rand()+1)/((double)RAND_MAX+1));
        if(!isConnectedTo(u, v))
            connect(u, v, weight);
        else
            e++;
    }

    return;
}


/** Conecta 2 vertices en un grafo.
*   @param u Vértice origen.
*   @param v Vértice destino.
*   @param w Peso de la arista que conecta u y v.
*/
void Graph::connect (int u, int v, double w){
    if(u == v) {
        printf("No se pueden conectar un nodo consigo mismo\n");
        exit(10);
    }

    edges[u].push_back(std::make_tuple(v, w));
    edges[v].push_back(std::make_tuple(u, w));
}


/** Verifica si dos vertices están conectados.
*   @param u Vértice origen.
*   @param v Vértice destino.
*   @return true si u y v están conectados, false en caso contrario.
*/
bool Graph::isConnectedTo(int u, int v) const{
    for(auto [z, _] : edges[u])
        if(z == v) return true;

    return false;
}


/** Obtiene el peso de la arista que conecta 2 vertices.
*   @param u Vértice origen.
*   @param v Vértice destino.
*   @return Peso de la arista que conecta u y v.
*/
double Graph::getWeight(int u, int v) const{
    for(auto [z, w] : edges[u])
        if(z == v) return w;

    std::cout << "Error en la arista de " << u << " a " << v << std::endl;
    exit(10);
}
