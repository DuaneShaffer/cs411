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
    
    vector<int> combination(sizeof(bridges));
    int max_possible_toll = 0;
    int temp = 0;
    
    vector<vector<int>> bad_bridge_combos;
    fill_bad_combos_vector(bad_bridge_combos, bridges);

    while (true) {
        
        if (!make_next_combo(combination))
            break;

        if (b_valid_combo(combination, bridges, bad_bridge_combos)){
            temp = get_combo_value(combination, bridges);
            if (temp > max_possible_toll)
                max_possible_toll = temp;
        }
    }
    return max_possible_toll;
}


void fill_bad_combos_vector(std::vector<std::vector<int>> & bad_bridge_combos, const std::vector<Bridge> & bridges){
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
}

bool make_next_combo(vector<int> & combos) {
    // counts up with binary numbers reversed
            // 2^0 on the left and powers increasing to the right
    for (int i = 0; i < combos.size(); ++i) {
        if (combos[i] == 0) {
            combos[i] = 1;
            return true;
        }
        if (i == combos.size()-1)
            return false;
        combos[i] = 0;
    }
}

bool b_valid_combo(const vector<int> & combination, const vector<Bridge> & bridges, 
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
