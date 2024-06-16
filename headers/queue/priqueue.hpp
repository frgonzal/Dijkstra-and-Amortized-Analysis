#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <tuple>


/** @class PriorityQueue
 * 
 *  Estructura de datos que permite almacenar pares de la forma (nodo, distancia) y obtener
 *  y eliminar el par con menor distancia. Además, permite modificar la distancia de un nodo
 *  en la cola.
 * 
 *  Operaciones necesarias:
 *   • Almacenar pares de la forma (nodo, distancia).
 *   • Obtener y eliminar el par con menor distancia.
 *   • Tener acceso directo desde cada nodo (por medio de un puntero) al par que lo representa,
 *       además de poder modificar su distancia con la función decreaseKey (en el contexto del
 *       algoritmo, no existe la necesidad de aumentar la distancia, solo de reducirla).
 *       
 */
class PriorityQueue {
public:
    /** Construye una cola a partir de una cantidad de elementos. 
     *  Se asume que los elementos son numerados de 0 a n-1.
     * 
     *  Todos los nodos tienen una distancia inicial de DBL_MAX, 
     *  excepto el nodo 0 que tiene distancia 0.
     * 
     *  @param n Cantidad de elementos de la cola.
     */
    virtual void heapify(int n) = 0;

    /** Extrae el par con menor distancia de la cola. 
     *  @return Tupla con el nodo y la distancia del nodo.
    */
    virtual std::tuple<int, double> extractMin() = 0;

    /** Disminuye el valor de un nodo en la cola. 
    *   @param node  Nodo a disminuir.
    *   @param value Nuevo valor del nodo.
    */
    virtual void decreaseKey(int node, double value) = 0;

    /** Verifica si la cola está vacía. */
    inline virtual bool empty() const = 0;
};


#endif