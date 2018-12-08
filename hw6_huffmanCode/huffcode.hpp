// huffcode.hpp 
// Duane Shaffer
// 7 December 2018
//
// For CS 411 Fall 2018
// Header file for huffman code algorithm
// Used in HW 6
// Based off code provided by Dr. Glen G Chappell and Dr. Chris Hartman

#ifndef FILE_HUFFCODE_H_INCLUDED
#define FILE_HUFFCODE_H_INCLUDED

#include <string>
#include <unordered_map>
#include <memory>
#include <queue>

struct Node {
    char character = 0;
    int weightVal = 0;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
};

// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {

// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, copy =, dctor used

// ***** HuffCode: general public functions *****
public:

    void setWeights(const std::unordered_map<char, int> & theweights);

    std::string encode(const std::string & text) const;

    std::string decode(const std::string & codestr) const;

// ***** HuffCode: data members *****
private:
    std::shared_ptr<Node> _tree;
    std::priority_queue<std::shared_ptr<Node>> _nodes;
    std::unordered_map<char,std::string> _codedLetters;

// ***** HuffCode: private member functions *****
private:
    void _seedNodeQueue(const std::unordered_map<char, int> & theweights);
    void _condenseNodesIntoATree();
    void _findCodedLetters(std::shared_ptr<Node> node, const std::string &word);
    
};  // End class HuffCode


#endif //#ifndef FILE_HUFFCODE_H_INCLUDED

