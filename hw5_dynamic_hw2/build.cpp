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
using std::max;

#include <iostream>
using std::cout;
using std::endl;

using Bridge = vector<int>;

int build(int w, int e, const vector<Bridge> & bridges) {

    vector<int> bridgeSubProblemAnswers((w+1)*(e+1));

    vector<vector<Bridge>> adj_list(w);
    for (const auto & i: bridges) {
        adj_list[i[0]].push_back(Bridge{i[1],i[2], 1});
    }

    for (auto & i: adj_list) {
        sort(i.begin(),i.end(), [](const Bridge & a, const Bridge & b) -> bool {
            if (a[0] < b[0])
                return true;
            else if (a[0] == b[0]) {
                if (a[1] > b[1])
                    return true;
                else
                    return false;
            }
            else
                return false;
        });
    }

    int starting_row = -1;
    int starting_column = -1;
    for (unsigned int i = 0; i < adj_list.size(); ++i) {
        if (!adj_list[i].empty()){
            starting_row = i;
            starting_column = adj_list[i][0][0];
            break;
        }
    }

    if (starting_row == -1)
        return 0;

    int max = 0;
    int temp;
    for (unsigned int i = starting_row; i < adj_list.size(); ++i) {
        for (unsigned int j = 0; j < adj_list[i].size(); ++j) {
            if (adj_list[i][j][0] <= starting_column) {
                // The current bridge is a possible starting point.
                // Do calculations with it.
                temp = solve_subproblem_recursive(adj_list, bridgeSubProblemAnswers, (int)i, (int)j, e);
                if (temp > max)
                    max = temp;
            }
            else 
                break;
        }
    }
    
    return max;

}

int solve_subproblem_recursive(const vector<vector<Bridge>> & adj_list, vector<int> & subproblem_answers, int i, int j, int east_cities) {
    
    // Make an if statement for if the chosen bridge at i,j has been solved
    if (subproblem_answers.at(i*east_cities+adj_list[i][j][0]) != 0) {
        return subproblem_answers.at(i*east_cities+adj_list[i][j][0]);
        }

    // Take diag and do things
    int currentMax = adj_list[i][j][1];
    int takeDiagMax = 0;
    for (auto i_copy = i+1 ; i_copy < (int)adj_list.size(); ++i_copy) {
        for (unsigned int columns = 0; columns < adj_list[i_copy].size(); ++columns ) {
            if (adj_list[i_copy][columns][0] > adj_list[i][j][0] && i_copy < (int)adj_list.size()) {
                takeDiagMax = max(takeDiagMax, solve_subproblem_recursive(adj_list, subproblem_answers, i_copy, columns, east_cities));
            }
        }
    }
    currentMax += takeDiagMax;
    
    // Same row but columns that are farther to the right
    for (auto columnCopy = j+1; columnCopy < (int)adj_list[i].size(); ++columnCopy){
            currentMax = max(currentMax, solve_subproblem_recursive(adj_list, subproblem_answers, i, columnCopy, east_cities));
        }

    // Same column but rows that are further down
    if ((i+1) < (int)adj_list.size()){
        for (auto rowcopy = i+1; rowcopy < (int)adj_list.size(); ++rowcopy) {
            for (auto columns = 0; columns < (int)adj_list[rowcopy].size(); ++columns) {
                if (adj_list[rowcopy][columns][0] > j)
                    break;
                if (adj_list[rowcopy][columns][0] == adj_list[i][j][0]) {
                    currentMax = max(currentMax, solve_subproblem_recursive(adj_list, subproblem_answers, rowcopy, columns, east_cities));
                }
            }
        }
    }
    subproblem_answers.at(i*east_cities+adj_list[i][j][0]) = currentMax;
    return currentMax;
}