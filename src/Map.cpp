#include <algorithm>
#include "Map.hpp"

std::vector<State> Map::get_neighbours(const State state)
{
    std::vector<State> valid_neighbours;

    for (const State n : state.neighbours())
        if (is_valid(state, n))
        {
            valid_neighbours.push_back(n);
        }

    return valid_neighbours;
}

bool Map::is_valid(const State current_state, const State next_state)
{   
    if (!next_state.location_in_range(0, width, 0, height))
    {
        return false;
    }

    for (Location static_obstacle : static_obstacles)
    {
        if (next_state.location_equals(static_obstacle))
        {
            return false;
        }
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