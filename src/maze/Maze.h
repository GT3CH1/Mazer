//
// Created by GT3CH1 on 7/23/24.
//

#ifndef MAZE_H
#define MAZE_H
#include <vector>

#include "MazeNode.h"
#include "types.h"

class Maze
{
private:
    std::vector<MazeNode> m_nodes;
    Size m_size;
    Point m_start;
    Point m_end;
    int m_seed;
    // static Maze* instance;

public:
    Maze(Size size, Point start, Point end, int seed);
    [[nodiscard]] int getDimension() const { return m_size.area(); }

    [[nodiscard]] MazeNode* get(const Point point)
    {
        // validate pos
        if (point.getX() >= 0 && point.getX() < m_size.x && point.getY() >= 0 && point.getY() < m_size.y)
            return get(point.getX(), point.getY());
        return nullptr;
    }

    [[nodiscard]] MazeNode* get(const int x, const int y)
    {
        return &m_nodes[y * m_size.x + x];
    }

    // static bool isInside(const Point point)
    // {
    //     return isInside(point.getX(), point.getY());
    // }
    //
    // static bool isInside(const int x, const int y)
    // {
    //     return x >= 0 && x < instance->m_size.x && y >= 0 && y < instance->m_size.y;
    // }

    void generate();
    int getSize() const { return m_size.x; }
};

// static Maze::instance = nullptr;

#endif //MAZE_H
