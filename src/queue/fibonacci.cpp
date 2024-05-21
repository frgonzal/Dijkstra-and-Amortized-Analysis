#include "../../headers/queue/fibonacci.hpp"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>


using namespace queue;


/** PUBLIC */

int Fibonacci::Node::childs(){
    int count = 0;
    Node *x = child;

    if(x == nullptr)
        return 0;

    do{
        count++;
        x = x->right;
    } while(x != child);

    return count;
}

void Fibonacci::heapify(int n){
    distances = new double[n];
    nodes = new Node*[n];

    this->n = n;
    this->size = 0;
    linkedList = nullptr;

    distances[0] = 0.0;
    nodes[0] = new Fibonacci::Node(0);
    min = nodes[0];
    insert(nodes[0]);

    for(int v=1; v<n; v++){
        distances[v] = DBL_MAX;
        nodes[v] = new Fibonacci::Node(v);
        insert(nodes[v]);
    }
}

void Fibonacci::consolidate(){
    //printf("size: %d\n", size);
    //std::vector<Node*> toMerge(std::ceil(std::log2((double)n)), nullptr);
    std::vector<Node*> toMerge(n, nullptr);
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
        if(toMerge[i] != nullptr)
            insert(toMerge[i]);
    }
}

std::tuple<int, double> Fibonacci::extractMin(){
    Node *x = min;
    while(x->child != nullptr){
        Node *y = x->child;
        y->parent = nullptr;
        cut(y);
        insert(y);
    }
    remove(x);

    int v = x->vertex;
    delete nodes[v];
    nodes[v] = nullptr;

    consolidate();
    return std::make_tuple(v, distances[v]);
}


void Fibonacci::decreaseKey(int node, double value){
    if(nodes[node] == nullptr)
        return;
    if(distances[node] < value)
        return;

    distances[node] = value;
    Node *x = nodes[node];

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


Fibonacci::~Fibonacci(){
    delete[] distances;
    delete[] nodes;
}


/** PRIVATE */

/** Une dos nodos en una lista doblemente enlazada */
void Fibonacci::link(Node* y, Node* x){
    if(y == nullptr){
        x->left = x;
        x->right = x;
        return;
    }
    // y <-> z and x
    Node *z = y->right;
    // y <-> x <-> z
    z->left = x;
    x->right = z;
    y->right = x;
    x->left = y;
}

/** Une dos B_k en un B_{k+1} */
Fibonacci::Node* Fibonacci::merge(Node* y, Node* x){
    if(distances[y->vertex] > distances[x->vertex])
        std::swap(x, y);

    x->parent = y;
    link(y->child, x);
    y->child = x;

    (y->degree)++;
    
    return y;
}


/** Realiza el corte de un nodo en la cola de Fibonacci. */
void Fibonacci::cut(Node* x){
    x->left->right = x->right;
    x->right->left = x->left;
    x->left = x;
    x->right = x;
    x->marked = false;

    if(x->parent != nullptr){

        Node *parent = x->parent;
        x->parent = nullptr;

        (parent->degree)--;

        if(parent->degree == 0)
            parent->child = nullptr;
        else
            parent->child = x->right;


        if(!parent->marked && parent->parent != nullptr)
            parent->marked = true;

        else if(parent->marked && parent->parent != nullptr){
            cut(parent);
            insert(parent);
        }
    }
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

    if(min == nullptr)
        min = x;

    /** update min */
    if(distances[x->vertex] < distances[min->vertex])
        min = x;

    size++;
}


/** Realiza el corte de un nodo. */
void Fibonacci::remove(Node* x){
    if(linkedList == x)
        linkedList = x->right;

    if(size == 1){
        linkedList = nullptr;
        min = nullptr;
    }

    x->left->right = x->right;
    x->right->left = x->left;

    x->right = x;
    x->left = x;

    if(min == x){
        min = nullptr;
    }

    size--;
}