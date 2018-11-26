// build.hpp
// Duane Shaffer
// 18 November 2018
//
// For CS 411 Fall 2018
// Header file for dynamic programming algorithm
// Used in HW 5

#ifndef BUILD_HPP
#define BUILD_HPP

#include <vector>

/* A bridge represents a size 3 vector with:
    * [0] = west-bank city
    * [1] = east-bank city
    * [2] = the toll collected 
*/
using Bridge = std::vector<int>;

int build(int w, int e, const std::vector<Bridge> & bridges);


int solve_subproblem_recursive(const std::vector<std::vector<Bridge>> & adj_list, std::vector<int> & subproblem_answers, int w, int e);


#endif //BUILD_HPP
