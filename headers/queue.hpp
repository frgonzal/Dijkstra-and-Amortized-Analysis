#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <tuple>

/** Definimos una estructura Q permita:
• Almacenar pares de la forma (distancia, nodo).
• Obtener y eliminar el par con menor distancia.
• Tener acceso directo desde cada nodo (por medio de un puntero) al par que lo representa,
además de poder modificar su distancia con la función decreaseKey (en el contexto del
algoritmo, no existe la necesidad de aumentar la distancia, solo de reducirla).*/
namespace queue {
    
    class Queue {
    public:
        Queue(int size);
        std::tuple<int, double> extractMin();
        void decreaseKey();
    };
}

#endif