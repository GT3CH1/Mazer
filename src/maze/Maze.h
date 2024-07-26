//
// Created by GT3CH1 on 7/23/24.
//

#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include "MazeNode.h"
#include "types.h"
#include "Solver.h"
#include "MazeGenerator.h"

class Maze
{
    static Point m_start;
    int m_seed{};
    Solver solver = Solver(Djikstra);
    static std::vector<MazeNode*>* m_nodes;
    static Size m_size;
    static Point m_end;
    MazeNode* playerPos;
    // static Maze* instance;
    MazeGenerator generator;

    static std::vector<bool> visited;

public:
    Maze(Size size, Point start);
    Maze(Size size, Point start, Point end, int seed);
    [[nodiscard]] static int getDimension() { return m_size.area(); }
    [[nodiscard]] bool playerSolved() const;
    static void generate(bool iterative = false);
    static MazeNode* getEnd() { return get(m_end); }
    static MazeNode* getStart() { return get(m_start); }

    static std::stack<MazeNode*> generationStack;

    [[nodiscard]] static MazeNode* get(const Point point)
    {
        // validate pos
        if (point.getX() >= 0 && point.getX() < m_size.x && point.getY() >= 0 && point.getY() < m_size.y)
            return get(point.getX(), point.getY());
        return nullptr;
    }

    [[nodiscard]] static MazeNode* get(const int x, const int y)
    {
        if (x < 0 || x >= m_size.x || y < 0 || y >= m_size.y)
            return nullptr;
        if(!m_nodes) {}
        return m_nodes->at(y * m_size.x + x);
    }

    static int getDistanceToGoal(const MazeNode* node);
    void movePlayer(Direction direction) const;
    std::set<MazeNode*> getVisitedNodes();
    static bool solved();
    static int getSize() { return m_size.x; }

    void reset(SolveType solveType);
    void reset();
    void setSolveType(SolveType type);
    [[nodiscard]] MazeNode* playerNode() const { return playerPos; }

    void doSolveMove()
    {
        if (!solved())
            solver.doMove();
    }

    static void generationReset()
    {
        // reset all walls on all nodes
        // for (auto node : m_nodes->data())
        // {
        //     node.resetWalls();
        // }
        for (auto node : *m_nodes)
        {
            node->resetWalls();
        }
        // clear the stack
        while (!generationStack.empty())
            generationStack.pop();
        visited = std::vector<bool>(m_size.area(), false);
        generationStack.push(get(m_start));
    }

    static std::vector<MazeNode*> getNeighbors(MazeNode node);
};


#endif //MAZE_H
