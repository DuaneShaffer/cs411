// Duane Shaffer
// CS411
// Fall 2018
// maxflow.hpp
// Header file for my implementation of the Ford-Fulkerson algorithm
// for finding max flow between a source and sink connected by edges.

#include <vector>
using adjMatrix = std::vector<std::vector<int>>;

int find_max_flow(adjMatrix&);
bool breadth_first_search(adjMatrix&, std::vector<int>& path);

