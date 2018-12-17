// Duane Shaffer
// CS411
// Fall 2018
// test_main.cpp
// Test program for max flow algorithm
// Uses the "Catch" unit-testing framework
// Requires maxFlowTests.cpp, catch.hpp, maxflow.hpp, maxflow.cpp
// This main altered from previous assignments from Dr. Glen G Chappell

#define CATCH_CONFIG_FAST_COMPILE
                             // Disable some features for faster compile
#define CATCH_CONFIG_RUNNER  // We write our own main
#include "catch.hpp"         // For the "Catch" unit-testing framework
#include <iostream>          // For std::cout, endl, cin


// Main program
// Run all tests. Prompt for ENTER before exiting.
int main(int argc, char *argv[])
{
    Catch::Session session;  // Primary Catch object
    int catchresult;         // Catch return code; for return by main

    // Handle command line
    catchresult = session.applyCommandLine(argc, argv);

    if (!catchresult)  // Continue only if no command-line error
    {
        // Run test suites
        std::cout << "BEGIN tests for max flow algorithm"
                  << " - CS 411 Assn 7"
                  << std::endl
                  << std::endl;
        catchresult = session.run();
        std::cout << "END tests for quicksort algorithm"
                  << " - CS 411 Assn 7"
                  << std::endl
                  << std::endl;
    }

    // Program return value is return code from Catch
    return catchresult;
}