#include "../headers/dijkstra.hpp"
#include "../headers/queue/queue.hpp"
#include <vector>
#include <tuple>
#include <float.h>

using namespace std;

tuple<vector<int>, vector<double>> dijkstra(const Graph& g, Queue& q){
    int n = g.edges.size();

    /* 1. Definimos dos arreglos de tamaño |V |, distancias y previos. */
    vector<int> previos(n, -1);
    vector<double> distancias(n, DBL_MAX);

    /* 3. Definimos la distancia del nodo raíz como 0, su nodo previo como −1, 
        y agregamos el par (distancia = 0, nodo = raíz) a Q */
    distancias[0] = 0;
    previos[0] = -1;
    //q.push(0, 0); ==> ya está en el heapify

    /*4. Por cada nodo v distinto de la raíz en el grafo:
        • Definimos distancias[v] como infinita y previos[v] como indefinido.
        • Agregamos el par (distancia = ∞, nodo = v) a Q. */
    // ==> ya están en el heapify y en el vector de distancias y previos

    /* 5. Se espera que la creación de Q se resuelva por medio de un Heapify, que transforme un array
        con las distancias en una cola en tiempo lineal (O(n)).*/
    /** hacer push y listo :v ??*/
    q.heapify(n);

    /* 6. Mientras Q no se encuentre vacío, repetimos: */
    while(!q.empty()){
        /* a) Obtenemos el par (d, v) con menor distancia en Q y lo eliminamos. */
        auto [v, d] = q.extractMin();

        /* b) Por cada vecino u del nodo v: */
        for(auto [u, w] : g.edges[v]){
            /* i. Si la distancia guardada para u (distancias[u]) es mayor a la distancia guardada para
            v (distancias[v]) más el peso de la arista (u, v), actualizamos el valor de la distancia
            de u, guardamos v como el nodo previo de u y actualizamos la distancia del par que
            representa al nodo u en Q utilizando decreaseKey. */
            if(distancias[u] > distancias[v] + w){
                distancias[u] = distancias[v] + w;
                previos[u] = v;
                q.decreaseKey(u, distancias[u]);
            }
        } 
    }

    /* 7. Retornamos el arreglo de previos y distancias.  */
    return make_tuple(std::move(previos), std::move(distancias));
}