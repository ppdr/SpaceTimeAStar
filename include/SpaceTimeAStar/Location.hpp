#pragma once

#include <cmath>
#include <iostream>

class Location
{
private:
    int x;
    int y;
public:
    Location(const int x, const int y) : x(x), y(y) {};
    bool operator==(const Location& other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator<(const Location& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
    float distance(const Location& other) const
    {
        return std::hypot(x - other.x, y - other.y);
    }
    Location offset(const int dx, const int dy) const
    {
        return Location(x + dx, y + dy);
    }
    bool in_range(const int x_min, const int x_max, const int y_min, const int y_max) const
    {
        return x >= x_min && x < x_max && y >= y_min && y < y_max;
    }
    // Print the location
    friend std::ostream& operator<<(std::ostream& os, const Location& loc)
    {
        os << loc.x << ", " << loc.y;
        return os;
    }
};
