#include "../headers/graph.hpp"
#include "../headers/queue/queue.hpp"
#include "../headers/queue/heap.hpp"
#include "../headers/queue/fibonacci.hpp"
#include "../headers/dijkstra.hpp"
#include <stdlib.h>
#include <iostream>
#include <float.h>
#include <memory>



int main(){
    while(true){
        Graph g((1<<8), (1<<10));

        //std::unique_ptr<Queue> heap_q = std::make_unique<queue::Heap>(queue::Heap());
        std::unique_ptr<Queue> fibo_q = std::make_unique<queue::Fibonacci>(queue::Fibonacci());

        // do not use until implemented
        dijkstra(g, fibo_q);
    }

    //fibo_q->heapify(10);
    return 0;
}