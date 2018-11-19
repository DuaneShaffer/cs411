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

class BridgeTollMaximizer {
public:
    BridgeTollMaximizer(const std::vector<Bridge> & bridges):
                                        _combination(sizeof(bridges)),
                                        _max_toll(0),
                                        _bridges(bridges),
                                        _bad_bridge_combos(bridges.size()){
        _fill_bad_combos_vector();
    }

    ~BridgeTollMaximizer() = default;

    int get_max_toll_value();

private:
    std::vector<int> _combination;
    int _max_toll;    
    const std::vector<Bridge> & _bridges;
    std::vector<std::vector<int>> _bad_bridge_combos;

    void _fill_bad_combos_vector();
    void _calculate_tolls_recursive(unsigned int slot = 0);
    bool _b_valid_combo();
    int _get_combo_value();    
};


#endif //BUILD_HPP
