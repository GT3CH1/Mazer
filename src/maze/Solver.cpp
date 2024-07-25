//
// Created by GT3CH1 on 7/24/24.
//

#include "Solver.h"

#include "Maze.h"

Solver::Solver(const SolveType solveType)
{
    setSolveType(solveType);
}


void Solver::push(MazeNode* node)
{
    visited.insert(node);
    switch (solveType)
    {
    case BFS:
        bfsQueue.push(node);
        break;
    case DFS:
        dfsStack.push(node);
        break;
    case Djikstra:
        aStarQueue.push(node);
        break;
    }
}

MazeNode* Solver::pop()
{
    MazeNode* node = nullptr;
    switch (solveType)
    {
    case BFS:
        if (!bfsQueue.empty())
        {
            node = bfsQueue.front();
            bfsQueue.pop();
        }
        break;
    case DFS:
        if (!dfsStack.empty())
        {
            node = dfsStack.top();
            dfsStack.pop();
        }
        break;
    case Djikstra:
        if (!aStarQueue.empty())
        {
            node = aStarQueue.top();
            aStarQueue.pop();
        }
        break;
    }
    return node;
}

bool Solver::isEmpty()
{
    switch (solveType)
    {
    case BFS:
        return bfsQueue.empty();
    case DFS:
        return dfsStack.empty();
    case Djikstra:
        return aStarQueue.empty();
    }
    return true;
}

void Solver::clear()
{
    switch (solveType)
    {
    case BFS:
        while (!bfsQueue.empty())
            bfsQueue.pop();
        break;
    case DFS:
        while (!dfsStack.empty())
            dfsStack.pop();
        break;
    case Djikstra:
        while (!aStarQueue.empty())
            aStarQueue.pop();
        break;
    }
}

void Solver::doMove()
{
    switch (solveType)
    {
    case BFS:
        {
            // pop the first element
            const auto node = pop();
            if (node == nullptr)
                break;
            node->setActive();
            // get the neighbors
            auto neighbors = Maze::getNeighbors(*node);
            // iterate through the neighbors, and push them to the queue if not visited
            for (auto neighbor : neighbors)
            {
                if (!neighbor->isVisited())
                {
                    neighbor->setVisited();
                    push(neighbor);
                    push(node);
                }
            }
        }
        break;
    case DFS:
        {
            // pop the first element
            const auto node = pop();
            if (node == nullptr)
                break;
            node->setActive();
            // get the first neighbor
            auto neighbors = Maze::getNeighbors(*node);
            for (auto neighbor : neighbors)
            {
                if (!neighbor->isVisited())
                {
                    neighbor->setVisited();
                    push(neighbor);
                    push(node);
                    return;
                }
            }
        }
        break;
    case Djikstra:
        {
            // pop the first element
            const auto node = pop();
            if (node == nullptr)
                break;
            node->setActive();
            // get the first neighbor
            auto neighbors = Maze::getNeighbors(*node);
            for (auto neighbor : neighbors)
            {
                if (!neighbor->isVisited())
                {
                    neighbor->setVisited();
                    push(neighbor);
                    push(node);
                    return;
                }
            }
        }
        break;
    }
}
