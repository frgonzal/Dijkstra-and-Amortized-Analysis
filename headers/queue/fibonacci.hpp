#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP
#include "priqueue.hpp"
#include <vector>
#include <float.h>


namespace queue {

    namespace Fib {
        /** Estructura de un nodo en la cola de Fibonacci. */
        struct Node {
            Node(int vertex) 
                : vertex(vertex), parent(nullptr), child(nullptr), left(this), right(this), marked(false), degree(0), distance(DBL_MAX){};

            ~Node() = default;

            const int vertex;     // vertice
            Node* parent;
            Node* child;    
            Node* left;
            Node* right;
            bool marked;
            int degree;     // grado del nodo, si es un B_k entonces degree = k
            double distance; // distancia al nodo raiz
        };
    }
    using Fib::Node;

    class Fibonacci : public PriorityQueue {
    public:
        /* Construye una cola */
        Fibonacci() = default;

        /** Destructor de la clase Fibonacci. */
        ~Fibonacci();

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
        inline bool empty() const override;

    private:
        /** Vector A para la consolidación de la cola de Fibonacci. */
        std::vector<Node*> toMerge;

        /** Nodos de la cola de Fibonacci,
        *   tal que nodes[v] es el nodo del vertice
        *   v en la cola de Fibonacci.
        */
        std::vector<Node> nodes;

        /** puntero al nodo con menor distancia en la cola. */
        Node* min;

        /** Puntero al primer nodo en la cola de Fibonacci. */
        Node* linkedList;

        /** Une dos nodos en la cola de Fibonacci. */
        inline void link(Node* x, Node* y);

        /** Une dos colas de Fibonacci. */
        Node* merge(Node* x, Node* y);

        /** Realiza la consolidación de la cola de Fibonacci. */
        inline void consolidate();

        /** Inserta un nodo en la cola de Fibonacci. */
        inline void insert(Node* x);

        /** Realiza el corte de un nodo en la lista enlazada. */
        inline void remove(Node* x);

        /** Realiza el corte de un nodo. */
        void cut(Node* x);
    };
}


#endif