#include <algorithm>
#include "Map.hpp"

std::vector<State> Map::get_neighbours(const State state)
{
    std::vector<State> neighbours;
    std::vector<State> neighbour_candidates = {
        state.neighbour(-1, 0),
        state.neighbour(1, 0),
        state.neighbour(0, -1),
        state.neighbour(0, 1),
        state.neighbour(0, 0),
    };

    for (State n : neighbour_candidates)
        if (is_valid(state, n))
        {
            neighbours.push_back(n);
        }

    return neighbours;
}

bool Map::is_valid(const State current_state, const State next_state)
{   
    // Check if the state is in the static obstacles
    if (std::find(static_obstacles.begin(), static_obstacles.end(), next_state.location) != static_obstacles.end())
    {
        return false;
    }

    // Check if the state is in the vertex constraints
    for (State vertex_constraint : vertex_constraints)
    {
        if (vertex_constraint == next_state)
        {
            return false;
        }
    }

    // Check if the state is in the edge constraints
    for (std::pair<State, State> edge_constraint : edge_constraints)
    {
        if (edge_constraint.first == current_state && edge_constraint.second == next_state)
        {
            return false;
        }
    }

    return true;
}