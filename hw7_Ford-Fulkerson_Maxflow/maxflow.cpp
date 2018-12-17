// Duane Shaffer
// CS411
// Fall 2018
// maxflow.cpp
// Source file for my implementation of the Ford-Fulkerson algorithm
// for finding max flow between a source and sink connected by edges.

#include <vector>
using std::vector;
#include <algorithm>
using std::min;
#include <queue>
using std::queue;
#include <climits>
#include "maxflow.hpp"

using adjMatrix = std::vector<std::vector<int>>;

int find_max_flow(adjMatrix& matrix){
    int curr_node, parent_node;
    int max_flow = 0;
    vector<int> path(matrix.size());
    while(breadth_first_search(matrix, path)){
        int path_flow=INT_MAX;
        for(curr_node=matrix.size()-1; curr_node != 0; curr_node = path[curr_node]){
            parent_node=path[curr_node];
            path_flow=min(path_flow, matrix[parent_node][curr_node]);
        }
        for(curr_node=matrix.size()-1; curr_node != 0; curr_node = path[curr_node]){
            parent_node = path[curr_node];
            matrix[parent_node][curr_node] -= path_flow;
            matrix[curr_node][parent_node] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

bool breadth_first_search(adjMatrix& matrix, vector<int>& path){
    queue <int> q;
    vector<bool> isVisited(matrix.size());

    q.push(0);
    isVisited[0] = true;

    while(!q.empty()){
        int curr_node = q.front();
        q.pop();
        for(unsigned int next_node = 0; next_node < matrix.size(); next_node++){
            if(isVisited[next_node] == false && matrix[curr_node][next_node] > 0){
                q.push(next_node);
                path[next_node] = curr_node;
                isVisited[next_node] = true;
            }
        }
    }
    return (isVisited.back()==true);
}

