#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <chrono>
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
    std::map<State, float> f_score;

    const Node start_node = Node(start, 0.0, map.get_heuristic(start, goal), nullptr);
    open_set.push(start_node);

    f_score[start] = map.get_heuristic(start, goal);

    const auto start_time = std::chrono::high_resolution_clock::now();
    expanded_node_count = 0;

    while (!open_set.empty())
    {
        Node current = open_set.top();

        expanded_node_count++;
        
        if (expanded_node_count > max_node_expansions)
        {
            success = false;
            
            const auto end_time = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double> elapsed_seconds = end_time - start_time;
            runtime = elapsed_seconds.count();

            return std::vector<State>();
        }
        
        if (current.is_at(goal))
        {
            success = true;

            const auto end_time = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double> elapsed_seconds = end_time - start_time;
            runtime = elapsed_seconds.count();

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

    success = false;
    
    const auto end_time = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    runtime = elapsed_seconds.count();

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

    std::cout << (astar.success ? "Success" : "Failed") << std::endl;

    for (State state : path)
    {
        std::cout << state << std::endl;
    }

    std::cout << "Expanded: " << astar.expanded_node_count << std::endl;
    std::cout << "Runtime: " << astar.runtime << "[s]" << std::endl;

    return 0;
}