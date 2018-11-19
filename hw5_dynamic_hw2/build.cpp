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

using Bridge = vector<int>;

int build(int w, int e, const vector<Bridge> & bridges) {
    auto bridges_copy = bridges;

    sort(bridges_copy.begin(),bridges_copy.end(), [](const Bridge & a, const Bridge & b) -> bool {
        if (a[0] < b[0])
            return true;
        else if (a[0] == b[0])
            return a[1] < b[1];
        else
            return false;
    });

    return 0;

}
