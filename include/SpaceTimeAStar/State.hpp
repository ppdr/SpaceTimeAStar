#pragma once

#include "Location.hpp"

class State {
    private:
        int t;
        Location location;
    public:
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
        bool location_in_range(const int x_min, const int x_max, const int y_min, const int y_max) const
        {
            return location.in_range(x_min, x_max, y_min, y_max);
        }
        const std::vector<State> neighbours() const
        {
            std::vector<State> neighbours = {
                State(t + 1, location.offset(0, 0)),
                State(t + 1, location.offset(0, 1)),
                State(t + 1, location.offset(0, -1)),
                State(t + 1, location.offset(1, 0)),
                State(t + 1, location.offset(-1, 0))
            };

            return neighbours;
        }
    friend std::ostream& operator<<(std::ostream& os, const State& state)
    {
        os << state.t << ": (" << state.location << ")";
        return os;
    }
};
