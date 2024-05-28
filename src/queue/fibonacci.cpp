#include "../../headers/queue/fibonacci.hpp"
#include <float.h>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace queue;
using namespace queue::Fib;

/** PUBLIC */

Fibonacci::~Fibonacci(){};

void Fibonacci::heapify(int n){
    distances.resize(n, DBL_MAX);
    nodes.reserve(n);

    toMerge.resize(std::ceil(std::log2((double)n))+1, nullptr);

    this->n = n;
    this->size = 0;
    linkedList = nullptr;

    distances[0] = 0.0;
    nodes.emplace_back(0);

    min = &nodes[0];
    insert(&nodes[0]);

    for(int v=1; v<n; v++){
        distances[v] = DBL_MAX;
        nodes.push_back(v);
        insert(&nodes[v]);
    }
}

void Fibonacci::consolidate(){
    while(linkedList != nullptr){
        Node* x = linkedList;
        remove(x);

        if(toMerge[x->degree] == nullptr){
            toMerge[x->degree] = x;
        } else {
            Node* y = toMerge[x->degree];
            toMerge[x->degree] = nullptr;
            Node* m = merge(y, x);
            insert(m);
        }
    }

    min = nullptr;
    for(int i=0; i<toMerge.size(); i++){
        if(toMerge[i] != nullptr){
            insert(toMerge[i]);
            if(min == nullptr || distances[toMerge[i]->vertex] < distances[min->vertex])
                min = toMerge[i];
            toMerge[i] = nullptr;
        }
    }
}

std::tuple<int, double> Fibonacci::extractMin(){
    Node *x = min;
    while(x->child != nullptr){
        Node *y = x->child;
        cut(y);
        insert(y);
    }
    remove(x);

    consolidate();
    return std::make_tuple(x->vertex, distances[x->vertex]);
}


void Fibonacci::decreaseKey(int node, double value){
    if(distances[node] <= value)
        return;

    distances[node] = value;
    Node *x = &nodes[node];

    if(distances[node] < distances[min->vertex])
        min = x;

    if(x->parent != nullptr && distances[node] < distances[x->parent->vertex]){
        cut(x);
        insert(x);
    }
}


bool Fibonacci::empty(){
    return (size == 0);
}


/** PRIVATE */

/** Une dos nodos en una lista doblemente enlazada */
void Fibonacci::link(Node* y, Node* x){
    if(y == nullptr)
        return;

    Node *z = y->right;

    z->left = x;
    x->right = z;
    y->right = x;
    x->left = y;
}

/** Une dos B_k en un B_{k+1} */
Node* Fibonacci::merge(Node* y, Node* x){
    if(distances[y->vertex] > distances[x->vertex])
        std::swap(x, y);

    if( distances[y->vertex] < distances[x->vertex] ){
        x->parent = y;
        link(y->child, x);
        y->child = x;
        (y->degree)++;
        return y;
    } else {
        y->parent = x;
        link(x->child, y);
        x->child = y;
        (x->degree)++;
        return x;
    }
    
    return nullptr;
}


/** Realiza el corte de un nodo en la cola de Fibonacci. */
void Fibonacci::cut(Node* x){
    if(x->parent != nullptr){
        Node *parent = x->parent;
        x->parent = nullptr;

        if(parent->child == x)
            parent->child = x->right;
        if(parent->child == x)
            parent->child = nullptr;
        (parent->degree)--;

        if(!parent->marked && parent->parent != nullptr)
            parent->marked = true;

        else if(parent->marked && parent->parent != nullptr){
            cut(parent);
            insert(parent);
        }
    }

    x->left->right = x->right;
    x->right->left = x->left;
    x->left = x;
    x->right = x;
    x->marked = false;
}


/** Inserta un nodo en la cola de Fibonacci. */
void Fibonacci::insert(Node* x){
    Node *first = linkedList;

    if(first == nullptr){
        linkedList = x;
        x->left = x;
        x->right = x;
    } else {
        Node *last = first->left;
        last->right = x;
        x->left = last;
        x->right = first;
        first->left = x;
    }

    size++;
}


/** Realiza el corte de un nodo. */
void Fibonacci::remove(Node* x){
    if (linkedList == x)
        linkedList = x->right;

    if (linkedList == x)
        linkedList = nullptr;

    if(min == x)
        min = nullptr;

    x->left->right = x->right;
    x->right->left = x->left;

    x->right = x;
    x->left = x;

    size--;
}