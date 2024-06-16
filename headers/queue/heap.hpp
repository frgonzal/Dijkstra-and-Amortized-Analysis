#ifndef HEAP_HPP
#define HEAP_HPP
#include "priqueue.hpp"
#include "vector"



namespace queue {

    /** Clase que implementa una cola de prioridad utilizando un heap.
     *  
     *  La cola de prioridad permite almacenar pares de la forma (nodo, distancia) y obtener
     *  y eliminar el par con menor distancia. Además, permite modificar la distancia de un nodo
     *  en la cola.
     */
    class Heap : public PriorityQueue {
    public:
        /* Construye una cola */
        Heap() = default;

        /** Destructor de la clase Heap. */
        ~Heap() = default;

        /** Construye una cola a partir de una cantidad de elementos. 
         *  Se asume que los elementos son numerados de 0 a n-1.
         * 
         *  Todos los nodos tienen una distancia inicial de DBL_MAX, 
         *  excepto el nodo 0 que tiene distancia 0.
         * 
         *  @param n Cantidad de elementos de la cola.
         */
        void heapify(int n) override;

        /** Extrae el par con menor distancia de la cola. 
         *  @return Tupla con el nodo y la distancia del nodo.
         */
        std::tuple<int, double> extractMin() override;

        /** Disminuye el valor de un nodo en la cola. 
        *   @param node  Nodo a disminuir.
        *   @param value Nuevo valor del nodo.
        */
        void decreaseKey(int node, double value) override;

        /** Verifica si la cola está vacía. */
        inline bool empty() const override;

    private:
        /** Cantidad de vertices en la cola. */
        int n;

        /** Cantidad de nodos en la cola, no confundir con n */
        int size;

        /**  Vector que almacena los nodos y sus distancias. */
        std::vector<std::pair<int, double>> heap;

        /**  Vector que almacena la posición de los nodos en el heap. */
        std::vector<int> position;

        /**  Función que sube un nodo en el heap. */
        void siftUp(int index);

        /**  Función que baja un nodo en el heap. */
        void siftDown(int index);

        /**  Función que encuentra el índice del hijo izquierdo de un nodo. */
        int leftChild(int index);

        /**  Función que encuentra el índice del hijo derecho de un nodo. */
        int rightChild(int index);

        /**  Función que encuentra el índice del padre de un nodo. */
        int parent(int index);
    };
}

#endif