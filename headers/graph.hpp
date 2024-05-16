#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <tuple>


struct Graph{
    std::vector<std::tuple<double, int>> edges;

    Graph() = default;
    Graph(int n);
};


#endif