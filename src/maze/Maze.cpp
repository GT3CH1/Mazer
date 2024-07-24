//
// Created by GT3CH1 on 7/23/24.
//

#include "Maze.h"

#include <stack>
// static Maze::instance = nullptr;
std::vector<MazeNode> Maze::m_nodes = std::vector<MazeNode>();
Size Maze::m_size = Size();
Point Maze::m_end = Point(0, 0);

Maze::Maze(Size size, Point start) : m_start(start)
{
    m_end = Point(size.x - 1, size.y - 1);
    m_start = start;
    srand(time(nullptr));
    // instance = this;
    m_size = size;
    generate();
    solver.push(get(m_start));}

Maze::Maze(const Size size, const Point start, const Point end, int seed) :
    m_start(start), m_seed(seed)
{
    srand(seed);
    // instance = this;
    m_size = size;
    m_end = end;

    generate();

    solver.push(get(m_start));
}

int Maze::getDistanceToGoal(const MazeNode* node)
{
    // get manhattan distance to goal
    const auto goal = get(m_end);
    const auto distance = abs(node->getPos().getX() - goal->getPos().getX()) + abs(
        node->getPos().getY() - goal->getPos().getY());
    return distance;
}

void Maze::generate() const
{
    m_nodes = std::vector<MazeNode>(m_size.x * m_size.y);
    // set pos for each node
    for (int y = 0; y < m_size.y; y++)
    {
        for (int x = 0; x < m_size.x; x++)
        {
            get(x, y)->setPos(Point(x, y));
        }
    }
    get(m_start)->setStart();
    get(m_end)->setGoal();
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
            const auto direction = node->getDirectionToNeighbor(neighbor);
            node->removeWall(direction, neighbor);
            // neighbor->removeWall(opposite(direction));
        }
    }
}

bool Maze::solved()
{
    // check if the goal node has been visited
    return get(m_end)->isVisited();
}

void Maze::reset(const SolveType solveType)
{
    setSolveType(solveType);
    reset();
}

void Maze::reset()
{
    for (auto& node : m_nodes)
    {
        node.reset();
    }
    solver.clear();
    solver.push(get(m_start));
}

void Maze::setSolveType(SolveType type)
{
    solver.setSolveType(type);
}

std::vector<MazeNode*> Maze::getNeighbors(const MazeNode node)
{
    auto neighbors = std::vector<MazeNode*>();
    for (const auto direction : {NORTH, SOUTH, WEST, EAST})
    {
        auto loc = node.move(direction);
        auto neighbor = get(loc.getX(), loc.getY());
        if (neighbor != nullptr && !node.hasWall(direction))
        {
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}
