//
// Created by GT3CH1 on 7/23/24.
//

#include "Maze.h"

#include <stack>

Maze::Maze(const Size size, const Point start, const Point end, int seed) :
    m_size(size), m_start(start), m_end(end), m_seed(seed)
{
    // instance = this;
    m_nodes = std::vector<MazeNode>(size.x * size.y);
    // set pos for each node
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            get(x, y)->setPos(Point(x, y));
        }
    }
    generate();
    get(m_start)->setStart();
    get(m_end)->setGoal();
}

void Maze::generate()
{
    auto stack = std::stack<MazeNode*>();
    auto visited = std::vector(m_size.area(), false);
    stack.push(get(m_start));
    visited[m_start.getY() * m_size.x + m_start.getX()] = true;
    while (!stack.empty())
    {
        auto node = stack.top();
        stack.pop();
        auto neighbors = std::vector<MazeNode*>();
        for (const auto direction : {NORTH, SOUTH, WEST, EAST})
        {
            auto neighbor = get(node->move(direction));
            if (neighbor == nullptr)
                continue;
            if (!visited[neighbor->getPos().getY() * m_size.x + neighbor->getPos().getX()])
            {
                neighbors.push_back(neighbor);
            }
        }
        // pick a random neighbor
        if (!neighbors.empty())
        {
            // check if neighbors is goal
            auto neighbor = neighbors[random() % neighbors.size()];
            stack.push(node);
            stack.push(neighbor);
            visited[neighbor->getPos().getY() * m_size.x + neighbor->getPos().getX()] = true;
            // remove wall between node and neighbor
            auto direction = node->getDirectionToNeighbor(neighbor);
            node->removeWall(direction, neighbor);
            // neighbor->removeWall(opposite(direction));
        }
    }
}
