// huffcode.cpp 
// Duane Shaffer
// 7 December 2018
//
// For CS 411 Fall 2018
// Source file for huffman code algorithm
// Used in HW 6
// Based off source code provided by Dr. Glen G Chappell and Dr. Chris Hartman

#include "huffcode.hpp"  // for class HuffCode declaration
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <memory>
using std::shared_ptr;
using std::make_shared;
#include <queue>
using std::priority_queue;

bool operator<(const shared_ptr<Node> &x, const shared_ptr<Node> &y)
{
    return x->weightVal > y->weightVal;
}

void HuffCode::setWeights(const unordered_map<char, int> & theweights)
{
    if (theweights.empty())
        return;

    if (theweights.size() == 1) {
        _codedLetters[theweights.begin()->first]='0';
        return;
    }

    _seedNodeQueue(theweights);    
    _condenseNodesIntoATree();
    _tree = _nodes.top();
    _createCodewords(_tree,"");

    
}

void HuffCode::_seedNodeQueue(const unordered_map<char, int> & theweights) {
    for(auto charValPair:theweights)
        _nodes.push(make_shared<Node>(Node{charValPair.first,charValPair.second}));
}

void HuffCode::_condenseNodesIntoATree() {
    while (_nodes.size()>1) {
        auto l = _nodes.top();
        _nodes.pop();
        auto r = _nodes.top();
        _nodes.pop();
        _nodes.push(make_shared<Node>(Node{0,l->weightVal+r->weightVal,l,r}));
    }
}

void HuffCode::_createCodewords(shared_ptr<Node> node, const string &word)
{
    if(node->character != 0) {
        _codedLetters[node->character] = word;
        return;
    }
    _createCodewords(node->left,word+"0");
    _createCodewords(node->right,word+"1");
}

string HuffCode::encode(const string & text) const
{
    string encodedString;
    for (char letter:text) {
        encodedString += _codedLetters.find(letter)->second;
    }
    return encodedString;
}


string HuffCode::decode(const string & codestr) const
{
    string decodedString;
    auto workingNode = _tree;
    for(auto bit:codestr){
        if (bit=='0')
            workingNode = workingNode->left;
        else
            workingNode = workingNode->right;
        if(workingNode->character != 0) {
            decodedString += workingNode->character;
            workingNode = _tree;
        }
    }
    return decodedString;
}
