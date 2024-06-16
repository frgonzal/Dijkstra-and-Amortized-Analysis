#include "../../headers/queue/fibonacci.hpp"
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace queue;
using namespace queue::Fib;

/** PUBLIC */

Fibonacci::~Fibonacci(){};

void Fibonacci::heapify(int n){
    toMerge.resize(std::ceil(std::log2((double)n)+1), nullptr);
    nodes.reserve(n);

    linkedList = nullptr;

    nodes.emplace_back(0);
    nodes[0].distance = 0.0;
    insert(&nodes[0]);

    for(int v=1; v<n; v++){
        nodes.emplace_back(v);
        insert(&nodes[v]);
    }

    min = &nodes[0];
}

inline void Fibonacci::consolidate(){
    while(linkedList != nullptr){
        Node* x = linkedList->right;
        remove(x);

        while(toMerge[x->degree] != nullptr){
            Node* y = toMerge[x->degree];
            toMerge[x->degree] = nullptr;
            x = merge(x, y);
        }
        toMerge[x->degree] = x;
    }

    //min = nullptr;
    for(int i=0; i<(int)toMerge.size(); i++){
        if(toMerge[i] != nullptr){
            insert(toMerge[i]);
            if(min == nullptr || toMerge[i]->distance < min->distance)
                min = toMerge[i];
            toMerge[i] = nullptr;
        }
    }
}

std::tuple<int, double> Fibonacci::extractMin(){
    Node *x = min;
    while(x->child != nullptr){
        Node *y = x->child->right;
        cut(y);
        insert(y);
    }
    remove(x);
    min = nullptr;

    consolidate();
    return std::make_tuple(x->vertex, x->distance);
}


void Fibonacci::decreaseKey(int node, double value){
    Node *x = &nodes[node];
    if(x->distance <= value)
        return;

    x->distance = value;

    if(x->distance < min->distance)
        min = x;

    if(x->parent != nullptr && x->distance < x->parent->distance){
        cut(x);
        insert(x);
    }
}


inline bool Fibonacci::empty() const {
    return (linkedList == nullptr);
}


/** PRIVATE */

/** Une dos nodos en una lista doblemente enlazada */
inline void Fibonacci::link(Node* x, Node* y){
    if(x == nullptr)
        return;

    Node *z = x->right;

    z->left = y;
    y->right = z;
    x->right = y;
    y->left = x;
}

/** Une dos B_k en un B_{k+1} */
Node* Fibonacci::merge(Node* x, Node* y){
    if( x->distance < y->distance ){
        y->parent = x;
        link(x->child, y);
        x->child = y;
        (x->degree)++;
        return x;
    } else {
        x->parent = y;
        link(y->child, x);
        y->child = x;
        (y->degree)++;
        return y;
    }
}


/** Realiza el corte de un nodo en la cola de Fibonacci. */
void Fibonacci::cut(Node* x){
    Node *parent = x->parent;
    x->parent = nullptr;

    if(parent->child == x){
        if(x->right == x)
            parent->child = nullptr;
        else
            parent->child = x->right;
    }
    (parent->degree)--;

    if(parent->parent != nullptr){
        if(!parent->marked){
            parent->marked = true;
        } else {
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
inline void Fibonacci::insert(Node* x){
    Node *first = linkedList;

    if(first == nullptr){
        linkedList = x;
    } else {
        Node *last = first->left;
        last->right = x;
        x->left = last;
        x->right = first;
        first->left = x;
    }
}


/** Realiza el corte de un nodo. */
inline void Fibonacci::remove(Node* x){
    if (linkedList == x){
        if (x->right == x)
            linkedList = nullptr;
        else
            linkedList = x->right;
    }

    x->left->right = x->right;
    x->right->left = x->left;

    x->right = x;
    x->left = x;
}