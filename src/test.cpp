#include "../headers/graph.hpp"
#include "../headers/queue/queue.hpp"
#include "../headers/queue/heap.hpp"
#include "../headers/queue/fibonacci.hpp"
#include "../headers/dijkstra.hpp"
#include <stdlib.h>


int main(){
    Graph g((1<<8), (1<<10));

    Queue heap_q = queue::Heap();
    Queue fibo_q = queue::Fibonacci();


    // do not use until implemented
    //dijkstra::dijkstra(g, q);

    return 0;
}