#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP
#include "queue.hpp"
#include <vector>


namespace queue {

    namespace Fib {
        /** Estructura de un nodo en la cola de Fibonacci. */
        struct Node {
            Node(int vertex) : vertex(vertex), parent(nullptr), child(nullptr), left(this), right(this), marked(false), degree(0){};
            ~Node() = default;

            const int vertex;     // vertice
            Node* parent;
            Node* child;    
            Node* left;
            Node* right;
            bool marked;
            int degree;     // grado del nodo, si es un B_k entonces degree = k
        };
    }
    using Fib::Node;

    class Fibonacci : public Queue {
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
        bool empty() override;

    private:
        /** Cantidad de vertices en la cola. */
        int n;

        /** Cantidad de nodos en la cola, no confundir con n! */
        int size;

        std::vector<double> distances;

        std::vector<Node*> toMerge;

        /** punteros a los nodos de las colas, 
        *   tal que nodes[v] es el nodo del vertice
        *   v en la cola de Fibonacci.
        */
        std::vector<Node*> nodes;

        /** puntero al nodo con menor distancia en la cola. */
        Node* min;

        Node* linkedList;

        /** Une dos nodos en la cola de Fibonacci. */
        void link(Node* y, Node* x);

        /** Une dos colas de Fibonacci. */
        Node* merge(Node* y, Node* x);

        /** Realiza la consolidación de la cola de Fibonacci. */
        void consolidate();

        /** Inserta un nodo en la cola de Fibonacci. */
        void insert(Node* x);

        /** Realiza el corte de un nodo en la lista enlazada. */
        void remove(Node* x);

        /** Realiza el corte de un nodo. */
        void cut(Node* x);
    };
}


#endif