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
    // Print the location
    friend std::ostream& operator<<(std::ostream& os, const Location& loc)
    {
        os << loc.x << ", " << loc.y;
        return os;
    }
};
