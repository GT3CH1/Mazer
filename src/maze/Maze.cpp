//
// Created by GT3CH1 on 7/23/24.
//

#include "Maze.h"

#include <stack>
// static Maze::instance = nullptr;
std::vector<MazeNode*>* Maze::m_nodes = new std::vector<MazeNode*>();
Size Maze::m_size = Size();
Point Maze::m_end = Point(0, 0);
Point Maze::m_start = Point(0, 0);
std::vector<bool> Maze::visited = std::vector<bool>();

bool Maze::playerSolved() const
{
    return playerPos->getPos() == m_end;
}


Maze::Maze(const Size size, const Point start): generator(MazeGenerator(size, start, Point(size.x - 1, size.y - 1)))
{
    playerPos = new MazeNode(start);
    m_end = Point(size.x - 1, size.y - 1);
    m_size = size;
    m_start = start;
    m_nodes = MazeGenerator::getMap();
}


int Maze::getDistanceToGoal(const MazeNode* node)
{
    // get manhattan distance to goal
    const auto goal = get(m_end);
    const auto distance = abs(node->getPos().getX() - goal->getPos().getX()) + abs(
        node->getPos().getY() - goal->getPos().getY());
    return distance;
}

void Maze::generate(const bool iterative)
{
    MazeGenerator::generationTick(iterative);
    m_nodes = MazeGenerator::getMap();
}

void Maze::movePlayer(Direction direction) const
{
    // check if node at current position has wall in direction
    auto nodeAtPlayerPos = get(playerPos->getPos());
    if (nodeAtPlayerPos == nullptr)
        return;

    if (nodeAtPlayerPos->hasWall(direction))
        return;
    // move player
    playerPos->setPos(playerPos->move(direction));
}

std::set<MazeNode*> Maze::getVisitedNodes()
{
    return solver.getVisitedNodes();
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
    for (const auto& node : *m_nodes)
    {
        node->reset();
    }
    visited.clear();
    solver.clear();
    solver.push(get(m_start));
    delete playerPos;
    playerPos = new MazeNode();
    playerPos->setPos(m_start);
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
