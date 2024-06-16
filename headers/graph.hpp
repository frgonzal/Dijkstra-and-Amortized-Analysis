#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <tuple>


/** @struct Estructura que representa un multi-grafo.
 * 
 *  Un grafo es un conjunto de vértices y aristas que los conectan
 *  cada arista tiene un peso asociado.
 * 
 *  El grafo puede contener aristar repetidas, es decir, puede tener
 *  múltiples aristas que conectan el mismo par de vértices.
 *   
 *  En este caso, el grafo es representado por una lista de adyacencia.
 *  Cada vértice tiene una lista de tuplas, donde cada tupla representa
 *  una arista que conecta el vértice con otro vértice y el peso de la arista.
 * 
 *  Por ejemplo, si edges[u] = [(v1, w1), (v2, w2), ...] significa que
 *  el vértice u está conectado con los vértices v1, v2, ... con pesos w1, w2, ...
 *  respectivamente.
 * 
 *  En este caso, los vértices son numerados de 0 a v-1.
 *  Las aristas son numeradas de 0 a e-1.
 *  Los pesos de las aristas son números reales.
*/
struct Graph{

    /* Lista de adyacencia del grafo. */
    std::vector<std::vector<std::tuple<int, double>>> edges;

    /** Constructor por defecto de la clase Graph. */
    Graph() = default;

    /** Destructor por defecto de la clase Graph. */
    ~Graph() = default;

    /** Constructor de la clase Graph.
    *   Genera un grafo con aristas aleatorias.
    *   @param v Cantidad de vértices del grafo.
    *   @param e Cantidad de aristas del grafo.
    */
    Graph(int v, int e, int seed);

    /** Conecta 2 vertices en un grafo.
    *   @param u Vértice origen.
    *   @param v Vértice destino.
    *   @param w Peso de la arista que conecta u y v.
    */
    void connect (int u, int v, double w);

    /** Verifica si dos vertices están conectados.
    *   @param u Vértice origen.
    *   @param v Vértice destino.
    *   @return true si u y v están conectados, false en caso contrario.
    */
    bool isConnectedTo(int u, int v) const;

    /** Obtiene el menor peso de las posibles aristas que conectan 2 vértices.
    *   @param u Vértice origen.
    *   @param v Vértice destino.
    *   @return Peso de la arista que conecta u y v.
    */
    double getWeight(int u, int v) const;
};


#endif