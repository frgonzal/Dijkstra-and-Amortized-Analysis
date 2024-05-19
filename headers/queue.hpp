#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <tuple>

/** Definimos una estructura Q permita:
• Almacenar pares de la forma (distancia, nodo).
• Obtener y eliminar el par con menor distancia.
• Tener acceso directo desde cada nodo (por medio de un puntero) al par que lo representa,
además de poder modificar su distancia con la función decreaseKey (en el contexto del
algoritmo, no existe la necesidad de aumentar la distancia, solo de reducirla).*/
class Queue {
public:

    /** Constructor por defecto de la clase Queue. */
    Queue() = default;

    /** Construye una cola a partir de una cantidad de elementos. */
    void heapify(int i);

    /** Inserta un par en la cola. */
    void push(int node, double value);

    /** Extrae el par con menor distancia de la cola. */
    std::tuple<int, double> extractMin();

    /** Disminuye el valor de un nodo en la cola. 
    *   @param node  Nodo a disminuir.
    *   @param value Nuevo valor del nodo.
    */
    void decreaseKey(int node, double value);

    /** Verifica si la cola está vacía. */
    bool empty();
};

#endif