#pragma once
#include <memory>
#include "Location.hpp"
#include "State.hpp"

class Node
{
private:
    float g_cost;
    float h_cost;
    float f_cost() const { return g_cost + h_cost; }
public:
    State state;
    // shared pointer to the parent node
    // Node* parent;
    std::shared_ptr<Node> parent;
    // Node() : state(State(0, Location(0, 0))), g_cost(0), h_cost(0), parent(nullptr) {};
    Node(const State state, const float g_cost, const float h_cost, std::shared_ptr<Node> parent)
    : state(state), g_cost(g_cost), h_cost(h_cost), parent(parent) {};
    // operator lt
    bool operator>(const Node& other) const
    {
        return f_cost() > other.f_cost();
    }
    bool is_at(const Location goal) const
    {
        return state.location_equals(goal);
    }
    float get_g_cost() const
    {
        return g_cost;
    }
    float get_f_cost() const
    {
        return f_cost();
    }
};
