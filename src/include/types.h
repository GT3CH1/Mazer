//
// Created by GT3CH1 on 7/24/24.
//

#ifndef TYPES_H
#define TYPES_H

enum Direction
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
};


class Size
{
public:
    explicit Size(const int width = 0, const int height = 0) : x(width), y(height)
    {
    }

    int x;
    int y;
    [[nodiscard]] int area() const { return x * y; }
};

class Point
{
public:
    Point() : x(0), y(0)
    {
    }

    Point(const int x, const int y) : x(x), y(y)
    {
    }

    [[nodiscard]] int getX() const { return x; }
    [[nodiscard]] int getY() const { return y; }
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }

    bool operator>(const Point& other) const
    {
        // calculate manhattan distance
        return x > other.x && y > other.y;
    }

    bool operator<(const Point& other) const { return x < other.x && y < other.y; }
    bool operator>=(const Point& other) const { return x >= other.x && y >= other.y; }

private:
    int x;
    int y;
};

#endif //TYPES_H
