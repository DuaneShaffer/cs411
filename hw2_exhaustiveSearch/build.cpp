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
    BridgeTollMaximizer btm(bridges);
    return btm.get_max_toll_value();

}


/**********************************************************
 * Functions for class BridgeTollMaximizer
 * ****************************************************/

int BridgeTollMaximizer::get_max_toll_value() {
    int temp = 0;

    while (true) {
        
        if (!_make_next_combo())
            break;

        temp = _get_combo_value();
        if (temp > _max_toll)
            if (_b_valid_combo()){
                _max_toll = temp;
            }
    }
    return _max_toll;
}

int BridgeTollMaximizer::_get_max_single_toll(const vector<Bridge> & bridges){
    int temp = 0;
    for(auto i : bridges) {
        if(i[2] > temp)
            temp = i[2];
    }
    return temp;
}

void BridgeTollMaximizer::_fill_bad_combos_vector(){
    int leftSide = 0;
    int rightSide = 1;

    for (int i=0; i < _bridges.size(); ++i){
        for (int j=i+1; j < _bridges.size(); ++j) {
            if (((_bridges[i][leftSide]<=_bridges[j][leftSide] && 
                    _bridges[i][rightSide] >= _bridges[j][rightSide])) || 
                ((_bridges[i][leftSide]>=_bridges[j][leftSide] && 
                    _bridges[i][rightSide] <= _bridges[j][rightSide]))){
                _bad_bridge_combos[i].push_back(j);
                }
        }
    }
}

bool BridgeTollMaximizer::_make_next_combo() {
    // counts up with binary numbers reversed
            // 2^0 on the left and powers increasing to the right
    for (int i = 0; i < _combination.size(); ++i) {
        if (_combination[i] == 0) {
            _combination[i] = 1;
            return true;
        }
        if (i == _combination.size()-1)
            return false;
        _combination[i] = 0;
    }
}

bool BridgeTollMaximizer::_b_valid_combo(){
    for (int i = 0; i < _bad_bridge_combos.size(); ++i) {
        for (int j = 0; j < _bad_bridge_combos[i].size(); ++j){
            if (_combination[i] == 1 && _combination[_bad_bridge_combos[i][j]] == 1) 
                return false;
        }
    }
    return true;
}

int BridgeTollMaximizer::_get_combo_value() {
    int cumulativeToll = 0;
    int tollVal = 2;

    for (int i = 0; i < _bridges.size(); ++i) {
        if (_combination[i] == 1)
            cumulativeToll += _bridges[i][tollVal];
    }
    return cumulativeToll;
}
