#include "queue.hpp"



namespace queue {

    class Heap : public Queue {
    public:
        /* Construye una cola */
        Heap() = default;

        /** Destructor de la clase Heap. */
        ~Heap();

        /** Construye una cola a partir de una cantidad de elementos. */
        void heapify(int n);

        /** Extrae el par con menor distancia de la cola. */
        std::tuple<int, double> extractMin();

        /** Disminuye el valor de un nodo en la cola. 
        *   @param node  Nodo a disminuir.
        *   @param value Nuevo valor del nodo.
        */
        void decreaseKey(int node, double value);

        /** Verifica si la cola está vacía. */
        bool empty();

    private:

    };
}