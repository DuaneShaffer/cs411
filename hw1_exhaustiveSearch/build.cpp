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
    
    while (true) {
        
        // make next combination (binary +1)
        // validate bridges
        // determine if value is new max
        save_if_new_max(combination, bridges, max_possible_toll);

        try{
        determine_if_finished(combination);
        } catch (...) {
            break;
        }
    }
    return max_possible_toll;
}

void save_if_new_max(const vector<int> & combination, const vector<Bridge> & bridges, int max) {

}

void determine_if_finished(const vector<int> & binary_number) {
    for (auto i : binary_number) {
        if (i ==0)
            return;
    }
    throw std::runtime_error("Finished with all numbers");
}