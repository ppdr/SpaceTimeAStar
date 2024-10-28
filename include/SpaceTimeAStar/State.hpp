#pragma once

#include "Location.hpp"

class State {
    private:
        int t;
    public:
        Location location;
        State(const int t, const Location loc) : t(t), location(loc) {};
        bool operator==(const State& other) const
        {
            return t == other.t && location == other.location;
        }
        bool operator<(const State& other) const {
            if (t != other.t) {
                return t < other.t;
            }
            return location < other.location;
        }
        bool location_equals(const Location& other) const
        {
            return location == other;
        }
        float distance(const Location& other) const
        {
            return location.distance(other);
        }
        State neighbour(const int dx, const int dy) const
        {
            return State(t + 1, location.neighbour(dx, dy));
        }
};
