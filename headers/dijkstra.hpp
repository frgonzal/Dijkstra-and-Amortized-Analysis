#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "graph.hpp"
#include "queue/queue.hpp"
#include <vector>
#include <tuple>


    
/** Dado un nodo raíz para un grafo con pesos positivos en sus aristas, encuentra el árbol de caminos
*   más cortos para ese nodo raíz, de modo que para cualquier otro nodo en el grafo, la distancia entre
*   la raíz y ese nodo es mínima para las aristas pertenecientes al árbol que los conectan. Este algoritmo
*   se describe de la siguiente manera.
*   @param g Grafo con pesos positivos en sus aristas.
*   @param q Estructura que permite obtener y eliminar el par con menor distancia.
*   @return Tupla con 2 vectores, el primero contiene los padres de cada nodo en el árbol de caminos más cortos
*           y el segundo contiene las distancias de cada nodo a la raíz.
*/ 
std::tuple<std::vector<int>, std::vector<double>> dijkstra(const Graph& g, Queue* q);

#endif