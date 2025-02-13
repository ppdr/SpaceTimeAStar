#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include "Location.hpp"
#include "State.hpp"
#include "Node.hpp"
#include "SpaceTimeAStar.hpp"

bool contains(std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq, const State& value) {
    while (!pq.empty()) {
        if (pq.top().state == value) {
            return true;
        }
        pq.pop();
    }
    return false;
}

std::vector<State> SpaceTimeAStar::solve(const State start, const Location goal)
{
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_set;
    std::set<State> closed_set;
    std::map<State, State*> came_from;
    std::map<State, float> g_score;
    std::map<State, float> f_score;

    const Node start_node = Node(start, 0.0, map.get_heuristic(start, goal), nullptr);
    open_set.push(start_node);

    // g_score[start] = 0;
    f_score[start] = map.get_heuristic(start, goal);
    // came_from[start] = nullptr;

    expanded_node_count = 0;

    while (!open_set.empty())
    {
        Node current = open_set.top();

        expanded_node_count++;
        
        if (current.is_at(goal))
        {
            std::vector<State> path;
            while (current.parent != nullptr)
            {
                path.push_back(current.state);
                current = *current.parent;
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        open_set.pop();

        closed_set.insert(current.state);

        for (State neighbour : map.get_neighbours(current.state))
        {
            if (closed_set.find(neighbour) != closed_set.end())
            {
                continue;
            }

            float tentative_f_score = current.get_g_cost() + 1 + map.get_heuristic(neighbour, goal);

            if (!contains(open_set, neighbour)){
                f_score[neighbour] = tentative_f_score;
                open_set.push(
                    Node(
                        neighbour,
                        current.get_g_cost() + 1,
                        map.get_heuristic(neighbour, goal),
                        std::make_shared<Node>(current)
                    )
                );
            } else {
                // If the neighbour is already in the open set
                if (tentative_f_score < f_score[neighbour]) {
                    f_score[neighbour] = tentative_f_score;
                    open_set.push(
                        Node(
                            neighbour,
                            current.get_g_cost() + 1,
                            map.get_heuristic(neighbour, goal),
                            std::make_shared<Node>(current)
                        )
                    );
                }
            }
        }
    }

    return std::vector<State>();
}

int main(int argc, char const *argv[])
{
    std::vector<Location> static_obstacles = {
        Location(1, 1),
        Location(2, 2),
        Location(3, 0)
    };

    std::vector<State> vertex_constraints = {
        State(0, Location(0, 0)),
        State(1, Location(1, 1)),
        State(2, Location(2, 2))
    };
    std::vector<std::pair<State, State>> edge_constraints = {
        std::make_pair(
            State(0, Location(0, 0)),
            State(1, Location(1, 1))
        )
    };

    Map map(static_obstacles, vertex_constraints, edge_constraints);

    SpaceTimeAStar astar(map, 1000000, 1.0);

    std::vector<State> path = astar.solve(State(0, Location(0, 0)), Location(3, 3));

    for (State state : path)
    {
        std::cout << state.location << std::endl;
    }

    std::cout << astar.expanded_node_count << std::endl;

    return 0;
}