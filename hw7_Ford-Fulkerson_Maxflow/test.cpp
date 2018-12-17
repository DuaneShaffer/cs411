// Duane Shaffer
// CS411
// Fall 2018
// test.cpp
// testing file for my implementation of the Ford-Fulkerson algorithm
// for finding max flow between a source and sink connected by edges.
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"
#include <iostream>
using std::cout;
using std::endl;
#include "maxflow.hpp"
#include <vector>
using std::vector;

using adjMatrix = std::vector<std::vector<int>>;

TEST_CASE("Simple") {
    adjMatrix matrix(6, vector<int> (6));
    matrix = {
                    {0, 16, 13, 0, 0, 0},
                    {0, 0, 10, 12, 0, 0},
                    {0, 4, 0, 0, 14, 0},
                    {0, 0, 9, 0, 0, 20},
                    {0, 0, 0, 7, 0, 4},
                    {0, 0, 0, 0, 0, 0}
                };
    REQUIRE(find_max_flow(matrix) == 23);
}
// little less simple
TEST_CASE("Little less simple") {
    adjMatrix matrix2(6, vector<int> (6));
    matrix2 = {
                {0, 20, 3, 0, 0, 0},     //0
                {0, 0, 2, 11, 0, 0},    //1
                {0, 0, 0, 7, 2, 0},     //2
                {0, 0, 0, 0, 6, 13},    //3
                {0, 0, 0, 0, 0, 6},     //4
                {0, 0, 0, 0, 0, 0}      //5
            };
    REQUIRE(find_max_flow(matrix2) == 16);
}