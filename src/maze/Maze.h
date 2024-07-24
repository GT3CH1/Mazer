//
// Created by GT3CH1 on 7/23/24.
//

#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include "MazeNode.h"
#include "types.h"
#include "Solver.h"

class Maze
{
    Point m_start;
    int m_seed{};
    Solver solver = Solver(Djikstra);
    static std::vector<MazeNode> m_nodes;
    static Size m_size;
    static Point m_end;

    // static Maze* instance;

public:
    Maze(Size size, Point start);
    Maze(Size size, Point start, Point end, int seed);
    [[nodiscard]] static int getDimension() { return m_size.area(); }

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
        return &m_nodes[y * m_size.x + x];
    }

    static int getDistanceToGoal(const MazeNode* node);
    void generate() const;
    static bool solved();
    static int getSize() { return m_size.x; }

    void reset(SolveType solveType);
    void reset();
    void setSolveType(SolveType type);

    void doSolveMove()
    {
        if (!solved())
            solver.doMove();
    }

    static std::vector<MazeNode*> getNeighbors(MazeNode node);
};


#endif //MAZE_H
