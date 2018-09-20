// build.cpp
// Duane Shaffer
// 20 September 2018
//
// For CS 411 Fall 2018
// Source file for exhaustive search algorithm
// Used in HW 2

#include "build.hpp"

#include <vector>
using std::vector;
#include <stdexcept>


using Bridge = vector<int>;

int build(int w, int e, const vector<Bridge> & bridges) {
    
    vector<int> combination(sizeof(bridges), 1);
    int max_possible_toll = 0;
    int temp = 0;
    
    while (true) {
        
        // make next combination (binary +1)
        // validate bridges
        // determine if value is new max

        temp = get_combo_value(combination, bridges);
        if (temp > max_possible_toll)
            max_possible_toll = temp;

        if (b_finished(combination))
            break;
    }
    return max_possible_toll;
}

int get_combo_value(const vector<int> & combination, const vector<Bridge> & bridges) {
    int temp = 0;
    for (int i = 0; i < bridges.size(); ++i) {
        if (combination[i] == 1)
            temp += bridges[i][2];
    }
    return temp;
}

bool b_finished(const vector<int> & binary_number) {
    for (auto i : binary_number) {
        if (i ==0)
            return false;
    }
    return true;
}