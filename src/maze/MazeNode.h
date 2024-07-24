//
// Created by GT3CH1 on 7/24/24.
//

#ifndef MAZENODE_H
#define MAZENODE_H
#include <cstdint>

#include "MazeWall.h"
#include "types.h"

class MazeNode
{
public:
    MazeNode() : m_pos(Point(0, 0))
    {
    }

    void setPos(const Point pos)
    {
        m_pos = pos;
    }

    [[nodiscard]] Point up() const
    {
        return {m_pos.getX(), m_pos.getY() - 1};
    }

    [[nodiscard]] Point down() const
    {
        return {m_pos.getX(), m_pos.getY() + 1};
    }

    [[nodiscard]] Point left() const
    {
        return {m_pos.getX() - 1, m_pos.getY()};
    }

    [[nodiscard]] Point right() const
    {
        return {m_pos.getX() + 1, m_pos.getY()};
    }

    [[nodiscard]] Point move(const Direction direction) const
    {
        auto pos = m_pos;
        switch (direction)
        {
        case NORTH:
            pos = up();
            break;
        case SOUTH:
            pos = down();
            break;
        case WEST:
            pos = left();
            break;
        case EAST:
        default:
            pos = right();
            break;
        }
        return pos;
    }

    Direction getDirectionToNeighbor(const MazeNode* node) const
    {
        if (node->up() == m_pos)
        {
            return SOUTH;
        }
        if (node->down() == m_pos)
        {
            return NORTH;
        }
        if (node->left() == m_pos)
        {
            return EAST;
        }
        return WEST;
    }

    void clearNeighborWall(MazeNode* neighbor)
    {
    }

    [[nodiscard]] Point getPos() const
    {
        return m_pos;
    }


    [[nodiscard]] bool hasWall(const MazeWall::MazeWall wall) const
    {
        return m_walls & wall;
    }

    void setWall(const MazeWall::MazeWall wall)
    {
        m_walls |= wall;
    }

    void clearWall(MazeWall::MazeWall wall)
    {
        m_walls &= ~wall;
    }

    void clearAllWalls()
    {
        m_walls = 0;
    }

    void setGoal()
    {
        m_isGoal = true;
    }

    void setStart()
    {
        m_isStart = true;
    }

    [[nodiscard]] bool isGoal() const
    {
        return m_isGoal;
    }

    [[nodiscard]] bool isStart() const
    {
        return m_isStart;
    }

    bool isValid() const
    {
        return m_pos.getX() >= 0 && m_pos.getY() >= 0;
    }

    void removeWall(Direction direction, MazeNode* neighbor)
    {
        switch (direction)
        {
        case NORTH:
            clearWall(MazeWall::NORTH);
            neighbor->clearWall(MazeWall::SOUTH);
            break;
        case SOUTH:
            clearWall(MazeWall::SOUTH);
            neighbor->clearWall(MazeWall::NORTH);
            break;
        case WEST:
            clearWall(MazeWall::WEST);
            neighbor->clearWall(MazeWall::EAST);
            break;
        case EAST:
            clearWall(MazeWall::EAST);
            neighbor->clearWall(MazeWall::WEST);
            break;
        }
    }

    void removeWall(Direction direction)
    {
        switch (direction)
        {
        case NORTH:
            clearWall(MazeWall::NORTH);
            break;
        case SOUTH:
            clearWall(MazeWall::SOUTH);
            break;
        case WEST:
            clearWall(MazeWall::WEST);
            break;
        case EAST:
            clearWall(MazeWall::EAST);
            break;
        }
    }

private:
    uint8_t m_walls = MazeWall::ALL;
    Point m_pos;
    bool m_isGoal = false;
    bool m_isStart = false;
};


#endif //MAZENODE_H
