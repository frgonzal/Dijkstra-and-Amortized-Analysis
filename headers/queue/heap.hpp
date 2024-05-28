#ifndef HEAP_HPP
#define HEAP_HPP
#include "priqueue.hpp"
#include "vector"



namespace queue {

    class Heap : public PriorityQueue {
    public:
        /* Construye una cola */
        Heap() = default;

        /** Destructor de la clase Heap. */
        ~Heap() = default;

        /** Construye una cola a partir de una cantidad de elementos. */
        void heapify(int n) override;

        /** Extrae el par con menor distancia de la cola. */
        std::tuple<int, double> extractMin() override;

        /** Disminuye el valor de un nodo en la cola. 
        *   @param node  Nodo a disminuir.
        *   @param value Nuevo valor del nodo.
        */
        void decreaseKey(int node, double value) override;

        /** Verifica si la cola está vacía. */
        bool empty() override;

    private:
        /** Cantidad de vertices en la cola. */
        int n;

        /** Cantidad de nodos en la cola, no confundir con n! */
        int size;

        std::vector<std::pair<int, double>> heap;

        std::vector<int> position;

        void siftUp(int index);

        void siftDown(int index);

        int leftChild(int index) { 
            return 2 * index + 1; 
        }

        int rightChild(int index) { 
            return 2 * index + 2; 
        }
        int parent(int index) { 
            return (index - 1) / 2; 
        }
    };
}

#endif