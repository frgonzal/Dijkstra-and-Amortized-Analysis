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
    Graph g((1<<8), (1<<10));

    std::unique_ptr<Queue> heap_q = std::make_unique<queue::Heap>(queue::Heap());
    std::unique_ptr<Queue> fibo_q = std::make_unique<queue::Fibonacci>(queue::Fibonacci());

    // do not use until implemented
    //dijkstra(g, fibo_q);


    fibo_q->heapify(10000);
    std::cout << fibo_q->empty() << std::endl;
    while(!fibo_q->empty()){
        auto[v, w] = fibo_q->extractMin();
        std::cout << v << " " << w << std::endl;

        if(v+1 < 10000)
        fibo_q->decreaseKey(v+1, rand());
    }

    //fibo_q->decreaseKey(1, 1);

    return 0;
}