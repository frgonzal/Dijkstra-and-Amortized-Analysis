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
    /** Construye una cola a partir de una cantidad de elementos. */
    virtual void heapify(int n) = 0;

    /** Extrae el par con menor distancia de la cola. */
    virtual std::tuple<int, double> extractMin() = 0;

    /** Disminuye el valor de un nodo en la cola. 
    *   @param node  Nodo a disminuir.
    *   @param value Nuevo valor del nodo.
    */
    virtual void decreaseKey(int node, double value) = 0;

    /** Verifica si la cola está vacía. */
    virtual bool empty() = 0;
};


#endif