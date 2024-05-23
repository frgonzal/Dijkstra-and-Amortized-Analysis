#include "../headers/graph.hpp"
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <stdio.h>




/** Constructor de la clase Graph.
*   Genera un grafo con aristas aleatorias.
*   @param v Cantidad de vértices del grafo.
*   @param e Cantidad de aristas del grafo.
*/
Graph::Graph(int v, int e){
    if(v < 2 || e < v - 1 || e > v*(v-1)/2){
        printf("No se puede generar un grafo con %d vértices y %d aristas\n", v, e);
        exit(10);
    }

    srand(time(NULL));
    edges.resize(v, std::vector<std::tuple<int, double>>());

    for(int i = 1; i < v; i++){

        /** w in (0, 1] */
        double weight = (((double)rand()+1)/((double)RAND_MAX+1));

        /** u in [1,..., i-1] */
        int u = (i > 1)? rand()%(i-1) + 1 : 0;

        connect(u, i, weight);
    }

    e -= (v - 1);
    while (e--){
        int a = rand() % v;
        while(edges[a].size() == v) a = rand() % v;

        int b = rand() % v;
        while(edges[b].size() == v || a == b || isConnectedTo(a, b)) b = rand() % v;

        double w = (((double)rand()+1)/((double)RAND_MAX+1));

        connect(a, b, w);

        //printf("Conectando %10d con %10d\n", a, b);
        //printf("e: %d", e);
    }
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

    return -1;
}
