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

int get_combo_value(const std::vector<int> & combination, const std::vector<Bridge> & bridges);
bool b_finished(const std::vector<int> & binaryNum);

#endif //BUILD_HPP