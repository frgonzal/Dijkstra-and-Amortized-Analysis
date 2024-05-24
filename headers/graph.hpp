#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <tuple>


/** Estructura que representa un grafo.
*/
struct Graph{

    /** Guarda la informacion de las aristas. */
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

    /** Obtiene el peso de la arista que conecta 2 vertices.
    *   @param u Vértice origen.
    *   @param v Vértice destino.
    *   @return Peso de la arista que conecta u y v.
    */
    double getWeight(int u, int v) const;
};


#endif