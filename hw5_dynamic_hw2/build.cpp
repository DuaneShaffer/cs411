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

    // Output the adjacency list
    // for (unsigned int i = 0; i < adj_list.size(); ++i) {
    //     cout << i << ": ";
    //     for (unsigned int j = 0; j < adj_list[i].size(); ++j) {
    //         cout << adj_list[i][j][0] << " ";    
    //     }
    //     cout <<  endl;
    // }

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
            if (adj_list[i][j][0] >= starting_column) {
                if (adj_list[i][j][2] == 1) {
                    // The current bridge is a possible starting point.
                    // Do calculations with it.
                    
                    // cout << "Column: " << adj_list[i][j][0] << endl;
                    temp = solve_subproblem_recursive(adj_list, bridgeSubProblemAnswers, (int)i, (int)j);
                    if (temp > max)
                        max = temp;
                        
                }
                else
                    break;
            }
            else 
                break;
        }
    }
    
    return max;

}

int solve_subproblem_recursive(const vector<vector<Bridge>> & adj_list, vector<int> & subproblem_answers, int i, int j) {
    
    // Make an if statement for if the chosen bridge at i,j has been solved
    if (subproblem_answers[i+i*adj_list[i][j][0]] != 0) {
        // cout << "Looking for: " << i+i*adj_list[i][j][0] << endl;
        return subproblem_answers[i+i*adj_list[i][j][0]];
        }


    // Take diag and do things
    int currentMax = adj_list[i][j][1];
    int takeDiagMax = 0;
    for (auto i_copy = i+1 ; i_copy < (int)adj_list.size(); ++i_copy) {
        // cout << "First loop i: " << i_copy << endl;
        for (unsigned int columns = 0; columns < adj_list[i_copy].size(); ++columns ) {
            // cout << "second loop i: " << i_copy << endl;
            if (adj_list[i_copy][columns][0] > adj_list[i][j][0]) {
                takeDiagMax = max(takeDiagMax, solve_subproblem_recursive(adj_list, subproblem_answers, i_copy, columns));
                // cout << "third loop i: " << i_copy << endl;
            }
        }
        // for (auto bridges: adj_list[i_copy]) {
        //     cout << "second loop i: " << i_copy << endl;
        //     if (bridges[0] > adj_list[i][j][0]) {
        //         takeDiagMax = max(takeDiagMax, solve_subproblem_recursive(adj_list, subproblem_answers, i_copy+1, bridges[0]));
        //         cout << "third loop i: " << i_copy << endl;
        //     }
        // }
    }
    currentMax += takeDiagMax;
    
    // cout << "Past first for loop" << endl;
    // Same row but columns that are farther to the right
    for (auto columnCopy = j+1; columnCopy < (int)adj_list[i].size(); ++columnCopy){
            currentMax = max(currentMax, solve_subproblem_recursive(adj_list, subproblem_answers, i, columnCopy));
        }

    // cout << "Past second for loop" << endl;
    // Same column but rows that are further down
    if ((i+1) < (int)adj_list.size()){
        for (auto rowcopy = i+1; rowcopy < (int)adj_list.size(); ++ rowcopy) {
            for (auto bridges: adj_list[rowcopy]) {
                if (bridges[0] > j)
                    break;
                if (bridges[0] == j) {
                    currentMax = max(currentMax, solve_subproblem_recursive(adj_list, subproblem_answers, rowcopy, j));
                }
            }
        }
    }
    // cout << "Storing the answer" << endl;
    subproblem_answers[i+i*adj_list[i][j][0]] = currentMax;
    return currentMax;
}