#pragma once

#include <vector>
#include <cmath>
#include "Location.hpp"
#include "State.hpp"


class Map
{
private:
    std::vector<Location> static_obstacles;
    std::vector<State> vertex_constraints;
    std::vector<std::pair<State, State>> edge_constraints;
public:
    Map(const std::vector<Location> static_obstacles, const std::vector<State> vertex_constraints, const std::vector<std::pair<State, State>> edge_constraints) : static_obstacles(static_obstacles), vertex_constraints(vertex_constraints), edge_constraints(edge_constraints) {};
    std::vector<State> get_neighbours(const State state);
    bool is_valid(const State current_state, const State next_state);
    float get_heuristic(const State state, const Location goal) {
        return state.distance(goal);
    };
};
