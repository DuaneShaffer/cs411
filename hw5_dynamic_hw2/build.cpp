// build.cpp
// Duane Shaffer
// 18 November 2018
//
// For CS 411 Fall 2018
// Source file for dynamic programming algorithm
// Used in HW 5

#include "build.hpp"

#include <vector>
using std::vector;

#include <algorithm>
using std::sort;

#include <iostream>
using std::cout;
using std::endl;

using Bridge = vector<int>;

int build(int w, int e, const vector<Bridge> & bridges) {
    vector<int> bridgeSubProblemAnswers((w+1)*(e+1));

    vector<vector<Bridge>> adj_list(w);
    for (const auto & i: bridges) {
        adj_list[i[0]].push_back(Bridge{i[1],i[2]});
    }

    for (auto & i: adj_list) {
        sort(i.begin(),i.end(), [](const Bridge & a, const Bridge & b) -> bool {
            if (a[0] < b[0])
                return true;
            else if (a[0] == b[0]) {
                if (a[1] > b[1])
                    return true;
                else
                    return false;
            }
            else
                return false;
        });
    }

    // Output the adjacency list
    // for (unsigned int i = 0; i < adj_list.size(); ++i) {
    //     cout << i << ": ";
    //     for (auto j: adj_list[i]) {
    //         cout << j[0] << " ";    
    //     }
    //     cout <<  endl;
    // }

    int starting_row, starting_column;
    for (unsigned int i = 0; i < adj_list.size(); ++i) {
        if (!adj_list[i].empty()){
            starting_row = i;
            starting_column = adj_list[i][0][0];
        }
    }

    return 0;

}
