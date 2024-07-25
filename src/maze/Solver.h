//
// Created by GT3CH1 on 7/24/24.
//

#ifndef SOLVER_H
#define SOLVER_H
#include <queue>
#include <set>
#include <stack>
#include "MazeNode.h"

enum SolveType
{
    BFS,
    DFS,
    Djikstra
};


class Solver
{
public:
    explicit Solver(SolveType solveType = BFS);

    void setSolveType(const SolveType solveType)
    {
        this->solveType = solveType;
    }

    void push(MazeNode* node);
    void doMove();
    void clear();
    MazeNode* pop();
    bool isEmpty();
    std::set<MazeNode*> getVisitedNodes() { return visited; }

private:
    SolveType solveType;
    std::queue<MazeNode*> bfsQueue;
    std::stack<MazeNode*> dfsStack;
    std::priority_queue<MazeNode*> aStarQueue;
    std::set<MazeNode*> visited;
};


#endif //SOLVER_H
