//
// Created by GT3CH1 on 7/24/24.
//

#include "MazeNode.h"


void MazeNode::setPos(const Point pos)
{
    m_pos = pos;
}

Point MazeNode::up() const
{
    return {m_pos.getX(), m_pos.getY() - 1};
}

Point MazeNode::down() const
{
    return {m_pos.getX(), m_pos.getY() + 1};
}

Point MazeNode::left() const
{
    return {m_pos.getX() - 1, m_pos.getY()};
}

Point MazeNode::right() const
{
    return {m_pos.getX() + 1, m_pos.getY()};
}

Point MazeNode::move(const Direction direction) const
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

Direction MazeNode::getDirectionToNeighbor(const MazeNode* node) const
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

void MazeNode::reset()
{
    // mark as unvisited
    m_visited = false;
    m_isActive = false;
}

void MazeNode::resetWalls()
{
    m_walls = MazeWall::ALL;
}

Point MazeNode::getPos() const
{
    return m_pos;
}

bool MazeNode::hasWall(const MazeWall::MazeWall wall) const
{
    return m_walls & wall;
}

bool MazeNode::hasWall(const Direction direction) const
{
    switch (direction)
    {
    case NORTH:
        return hasWall(MazeWall::NORTH);
    case SOUTH:
        return hasWall(MazeWall::SOUTH);
    case WEST:
        return hasWall(MazeWall::WEST);
    case EAST:
    default:
        return hasWall(MazeWall::EAST);
    }
}

void MazeNode::setWall(const MazeWall::MazeWall wall)
{
    m_walls |= wall;
}

void MazeNode::clearWall(const MazeWall::MazeWall wall)
{
    m_walls &= ~wall;
}

void MazeNode::clearAllWalls()
{
    m_walls = 0;
}

bool MazeNode::posValid() const
{
    return m_pos.getX() >= 0 && m_pos.getY() >= 0;
}

void MazeNode::visit()
{
    m_visited = true;
}

void MazeNode::setActive()
{
    m_isActive = true;
}

bool MazeNode::isActive() const
{
    return m_isActive;
}

bool MazeNode::isVisited() const
{
    return m_visited;
}

void MazeNode::removeWall(const Direction direction, MazeNode* neighbor)
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

void MazeNode::removeWall(const Direction direction)
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
