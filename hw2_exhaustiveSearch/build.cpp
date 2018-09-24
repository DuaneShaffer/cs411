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

#include <algorithm>
using std::find;

using Bridge = vector<int>;

int build(int w, int e, const vector<Bridge> & bridges) {
    BridgeTollMaximizer btm(bridges);
    return btm.get_max_toll_value();

}


/**********************************************************
 * Functions for class BridgeTollMaximizer
 * ****************************************************/

int BridgeTollMaximizer::get_max_toll_value() {
    _calculate_tolls_recursive();
    return _max_toll;
}

int BridgeTollMaximizer::_get_max_single_toll(const vector<Bridge> & bridges){
    int max = 0;
    int tollVal = 2;

    for(auto bridge : bridges) {
        if(bridge[tollVal] > max)
            max = bridge[tollVal];
    }
    return max;
}

void BridgeTollMaximizer::_fill_bad_combos_vector(){
    int leftSide = 0;
    int rightSide = 1;

    for (unsigned int i=0; i < _bridges.size(); ++i){
        for (unsigned int j=i+1; j < _bridges.size(); ++j) {
            if (((_bridges[i][leftSide]<=_bridges[j][leftSide] && 
                    _bridges[i][rightSide] >= _bridges[j][rightSide])) || 
                ((_bridges[i][leftSide]>=_bridges[j][leftSide] && 
                    _bridges[i][rightSide] <= _bridges[j][rightSide]))){
                _bad_bridge_combos[i].push_back(j);
                }
        }
    }
}

void BridgeTollMaximizer::_calculate_tolls_recursive(unsigned int slot) {
    if (slot == _good_bridge_combos.size()) {
        auto temp = _get_combo_value();
        if (temp > _max_toll)
            _max_toll = temp;
        return;
    }
    if (_combination[slot] == 0) {
        _combination[slot] = 1;
        if (_b_valid_combo())
            _calculate_tolls_recursive(slot+1);
        _combination[slot] = 0;
    }
    _calculate_tolls_recursive(slot+1);

}

bool BridgeTollMaximizer::_b_valid_combo(){
    for (unsigned int i = 0; i < _bad_bridge_combos.size(); ++i) {
        for (unsigned int j = 0; j < _bad_bridge_combos[i].size(); ++j){
            if (_combination[i] == 1 && _combination[_bad_bridge_combos[i][j]] == 1) 
                return false;
        }
    }
    return true;
}

int BridgeTollMaximizer::_get_combo_value() {
    int cumulativeToll = 0;
    int tollVal = 2;

    for (unsigned int i = 0; i < _bridges.size(); ++i) {
        if (_combination[i] == 1)
            cumulativeToll += _bridges[i][tollVal];
    }
    return cumulativeToll;
}
