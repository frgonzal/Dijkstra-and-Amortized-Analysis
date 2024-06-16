#include "../../headers/queue/heap.hpp"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>


using namespace queue;


void Heap::heapify(int n) {
    this->n = n; 
    this->size = n;
    heap.resize(n); 
    position.resize(n, -1); 

    for (int i = 0; i < n; ++i) {
        double initialDistance = (i == 0) ? 0.0 : DBL_MAX; // La distancia del nodo raíz (0) es 0, las demás son infinito
        heap[i] = {i, initialDistance}; // Metemos el par (nodo, distancia) al heap
        position[i] = i; // Guardamos la posicion del nodo en el vector position
    }

    for (int i = parent(n - 1); i >= 0; --i) {
        siftDown(i);
    }
}

/** Extrae el par con menor distancia de la cola. */
std::tuple<int, double> Heap::extractMin() {
    if (empty()) { 
        printf("Error: Heap is empty\n");
        exit(1);
    }

    // Recuperamos el nodo con distancia minima (la raiz)
    auto minNode = heap[0];
    auto minElem = std::make_tuple(minNode.first, minNode.second); 

    // Intercambiamos la raiz con el ultimo nodo para eliminarlo
    std::swap(heap[0], heap[size - 1]); 
    --size; 

    // Actualizar el nuevo nodo raiz
    if (size > 0) {
        position[heap[0].first] = 0; 
        siftDown(0);
    }

    position[minNode.first] = -1; 
    return minElem; 
}


void Heap::decreaseKey(int node, double value) {
    int index = position[node];

    if (index == -1 || heap[index].second <= value) {
        printf("Error: El nuevo valor del nodo es mayor o igual al anterior\n");
        exit(1);
    }

    heap[index].second = value; 
    siftUp(index);
}


inline bool Heap::empty() const {
    return size == 0; 
}


void Heap::siftDown(int index) {
    int minIndex = index; 
    
    int left = leftChild(index);
    if (left < size && heap[left].second < heap[minIndex].second) { 
        minIndex = left;
    }

    int right = rightChild(index); 
    if (right < size && heap[right].second < heap[minIndex].second) { 
        minIndex = right;
    }
    
    if (index != minIndex) { 
        std::swap(heap[index], heap[minIndex]);
        position[heap[index].first] = index; 
        position[heap[minIndex].first] = minIndex; 
        siftDown(minIndex); 
    }
}


void Heap::siftUp(int index) {
    while (index > 0 && heap[index].second < heap[parent(index)].second) { 
        std::swap(heap[index], heap[parent(index)]); 
        position[heap[index].first] = index; 
        position[heap[parent(index)].first] = parent(index); 
        index = parent(index); 
    }
}


int Heap::leftChild(int index) { 
    return 2 * index + 1; 
}


int Heap::rightChild(int index) { 
    return 2 * index + 2; 
}


int Heap::parent(int index) { 
    return (index - 1) / 2; 
}