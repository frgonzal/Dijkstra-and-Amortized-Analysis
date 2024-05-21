#include "../../headers/queue/heap.hpp"


using namespace queue;

/** Construye una cola a partir de una cantidad de elementos. */
void Heap::heapify(int n){
    return;
}

/** Extrae el par con menor distancia de la cola. */
std::tuple<int, double> Heap::extractMin(){
    return std::make_tuple(0, 0.0);
}

/** Disminuye el valor de un nodo en la cola. 
*   @param node  Nodo a disminuir.
*   @param value Nuevo valor del nodo.
*/
void Heap::decreaseKey(int node, double value){
    return;
}

/** Verifica si la cola está vacía. */
bool Heap::empty(){
    return true;
}