//
// Created by GT3CH1 on 7/25/24.
//

#include "MazeGenerator.h"
Size MazeGenerator::m_size;
Point MazeGenerator::m_start;
Point MazeGenerator::m_end;

std::stack<MazeNode*> MazeGenerator::generationStack;
std::vector<bool> MazeGenerator::visited;
std::vector<MazeNode*>* MazeGenerator::map = new std::vector<MazeNode*>();

MazeGenerator::MazeGenerator(const Size size, const Point start, const Point end)
{
    m_size = size;
    m_start = start;
    m_end = end;
    visited = std::vector<bool>(m_size.area());
    reset();
}


MazeNode* MazeGenerator::get(const Point position)
{
    return get(position.getX(), position.getY());
}

MazeNode* MazeGenerator::get(const int x, const int y)
{
    if (x < 0 || x >= m_size.x || y < 0 || y >= m_size.y)
        return nullptr;
    return map->at(y * m_size.x + x);
}

void MazeGenerator::psuedorandomDfsTick()
{
    const auto node = generationStack.top();
    generationStack.pop();
    if (node == nullptr)
        return;
    // mark node as visited
    auto neighbors = std::vector<MazeNode*>();
    for (const auto direction : {NORTH, SOUTH, WEST, EAST})
    {
        auto neighbor = get(node->move(direction));
        if (neighbor == nullptr)
            continue;
        auto neighborPos = neighbor->getPos();
        if (const auto neighborVisited = visited[neighborPos.getY() * m_size.x + neighborPos.getX()]; !neighborVisited)
        {
            neighbors.push_back(neighbor);
        }
    }
    // pick a random neighbor
    if (!neighbors.empty())
    {
        // check if neighbors is goal
        const auto neighbor = neighbors[random() % neighbors.size()];
        generationStack.push(node);
        generationStack.push(neighbor);
        visited[neighbor->getPos().getY() * m_size.x + neighbor->getPos().getX()] = true;
        visited[node->getPos().getY() * m_size.x + node->getPos().getX()] = true;
        // remove wall between node and neighbor
        const auto direction = node->getDirectionToNeighbor(neighbor);
        node->removeWall(direction, neighbor);
    }
}

void MazeGenerator::reset()
{
    generationStack = std::stack<MazeNode*>();
    // reset visited
    visited.clear();
    visited.resize(m_size.area());
    // clear all nodes
    delete map;
    map = new std::vector<MazeNode*>(m_size.area());
    for (int y = 0; y < m_size.y; y++)
    {
        for (int x = 0; x < m_size.x; x++)
        {
            const auto node = new MazeNode(Point(x, y));
            map->at(y * m_size.x + x) = node;
        }
    }
    get(m_start)->setStart();
    get(m_end)->setGoal();

    generationStack.push(get(m_start));
}

std::vector<MazeNode*>* MazeGenerator::generationTick(const bool iterative)
{
    if (!iterative)
    {
        while (!generationStack.empty())
        {
            psuedorandomDfsTick();
        }
        return map;
    }
    if (!generationStack.empty())
    {
        psuedorandomDfsTick();
    }
    return map;
}

bool MazeGenerator::doneGenerating()
{
    auto done = generationStack.empty();
    for (const auto visit : visited)
    {
        done &= visit;
    }
    return done;
}
