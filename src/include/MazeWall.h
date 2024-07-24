//
// Created by GT3CH1 on 7/24/24.
//

#ifndef MAZEWALL_H
#define MAZEWALL_H
#include "types.h"

namespace MazeWall
{
    enum MazeWall
    {
        NORTH = 0b1000,
        EAST = 0b0100,
        SOUTH = 0b0010,
        WEST = 0b0001,
        ALL = 0b1111,
        NONE = 0b0000
    };

    inline MazeWall getOppositeWall(const Direction direction)
    {
        switch (direction)
        {
        case Direction::NORTH:
            return SOUTH;
        case Direction::EAST:
            return WEST;
        case Direction::SOUTH:
            return NORTH;
        case Direction::WEST:
            return EAST;
        default:
            return NONE;
        }
    }

    inline MazeWall getOppositeWall(const MazeWall wall)
    {
        switch (wall)
        {
        case NORTH:
            return SOUTH;
        case EAST:
            return WEST;
        case SOUTH:
            return NORTH;
        case WEST:
            return EAST;
        default:
            return NONE;
        }
    }

    inline MazeWall getWall(const Direction direction)
    {
        switch (direction)
        {
        case Direction::NORTH:
            return NORTH;
        case Direction::EAST:
            return EAST;
        case Direction::SOUTH:
            return SOUTH;
        case Direction::WEST:
            return WEST;
        default:
            return NONE;
        }
    }
}
#endif //MAZEWALL_H
