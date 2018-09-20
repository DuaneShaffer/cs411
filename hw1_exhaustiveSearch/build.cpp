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

#include <iostream>
using std::cout;
using std::endl;


using Bridge = vector<int>;

int build(int w, int e, const vector<Bridge> & bridges) {
    
    vector<int> combination(sizeof(bridges), 1);
    int max_possible_toll = 0;
    int temp = 0;
    
    vector<vector<int>> bad_bridge_combos;
    int leftSide = 0;
    int rightSide = 1;

    for (int i=0; i < bridges.size(); ++i){
        for (int j=i+1; j < bridges.size(); ++j) {
            if (((bridges[i][leftSide]<=bridges[j][leftSide] && bridges[i][rightSide] >= bridges[j][rightSide])) || 
                ((bridges[i][leftSide]>=bridges[j][leftSide] && bridges[i][rightSide] <= bridges[j][rightSide]))){
                bad_bridge_combos.push_back(vector<int>{i,j});
                }
        }
    }

    while (true) {
        
        // make next combination (binary +1)
        // validate bridges

        if (b_valid_combo(combination, bridges, bad_bridge_combos)){
            temp = get_combo_value(combination, bridges);
            if (temp > max_possible_toll)
                max_possible_toll = temp;
        }
        if (b_finished(combination))
            break;
        }
    return max_possible_toll;
}


void fill_bad_combos_vector(std::vector<std::vector<int>> & bad_bridge_combos, const std::vector<Bridge> & bridges){

}

bool b_valid_combo(const std::vector<int> & combination, const vector<Bridge> & bridges, 
                    const vector<vector<int>> & bad_bridge_combos){
    for (auto i : bad_bridge_combos) {
        if (combination[i[0]]==1 && combination[i[1]] ==1) 
            return false;
    }
    return true;
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