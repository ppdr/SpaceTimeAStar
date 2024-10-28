#pragma once

#include <vector>
#include "Location.hpp"
#include "State.hpp"
#include "Node.hpp"
#include "Map.hpp"

class SpaceTimeAStar
{
private:
    Map map;
    int max_node_expansions;
    double timeout;
    
public:
    double runtime;
    int expanded_node_count;
    SpaceTimeAStar(const Map map, const int max_node_expansions, const double timeout) : map(map), max_node_expansions(max_node_expansions), timeout(timeout) {};
    std::vector<State> solve(const State start, const Location goal);
};
