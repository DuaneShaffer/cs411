// build.hpp
// Duane Shaffer
// 20 September 2018
//
// For CS 411 Fall 2018
// Header file for exhaustive search algorithm
// Used in HW 2

#ifndef BUILD_HPP
#define BUILD_HPP

#include <vector>

using Bridge = std::vector<int>;

int build(int w, int e, const std::vector<Bridge> & bridges);

void fill_bad_combos_vector(std::vector<std::vector<int>> & bad_combos, const std::vector<Bridge> & bridges);
bool make_next_combo(std::vector<int> & combos);
bool b_valid_combo(const std::vector<int> & binaryNum, const std::vector<Bridge> & bridges, 
                    const std::vector<std::vector<int>> & bad_bridge_combos);
int get_combo_value(const std::vector<int> & combination, const std::vector<Bridge> & bridges);

#endif //BUILD_HPP