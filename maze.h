//
// Created by GT3CH1 on 7/23/24.
//

#ifndef MAZE_H
#define MAZE_H
#include <queue>
#include <deque>
#include <iostream>
#include <stack>

enum MOVE_TYPE
{
    DFS = 0,
    BFS = 1,
    A_STAR = 2
};

enum DIRECTION
{
    NONE = -1,
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

class AStarNode
{
private:
    int pos;
    int distance;

public:
    AStarNode(int pos, int distance) : pos(pos), distance(distance)
    {
    }

    int getPos() const
    {
        return pos;
    }

    int getDistance() const
    {
        return distance;
    }

    bool operator<(const AStarNode& other) const
    {
        return distance > other.distance;
    }

    bool operator>(const AStarNode& other) const
    {
        return distance < other.distance;
    }
};

enum MAZE_SQUARE_TYPE
{
    WALL = 0,
    EMPTY = 1,
    START = 2,
    GOAL = 3,
    VISITED = 4,
    ACTIVE = 5,
    QUEUED = 6
};

class maze
{
private:
    int dimension = 0;
    int m_goal = 0;
    int m_start = 0;
    int m_curr_pos = 0;
    MOVE_TYPE m_move_type = DFS;
    std::stack<int> m_stack;
    std::queue<int> m_queue;
    std::priority_queue<AStarNode> m_priority_queue;
    // double array to store the maze
    std::vector<int> backend;

public:
    void set_move_type(MOVE_TYPE moveType)
    {
        m_move_type = moveType;
    }

    MOVE_TYPE get_move_type()
    {
        return m_move_type;
    }

    void initialize_map(int const dimension);

    explicit maze(int const dimension = 5, int const start = 0, MOVE_TYPE moveType = DFS) : dimension(dimension)
    {
        // allocate memory for the maze
        m_goal = dimension * dimension - 1;
        m_start = start;
        m_stack = std::stack<int>();
        m_curr_pos = start;
        m_move_type = moveType;
        m_queue.push(start);

        m_priority_queue.emplace(start, calculateManhattanDistance(start));
        initialize_map(dimension);
    }

    bool hasSolution() const;

    int getDimension() const
    {
        return dimension;
    }

    int get(int x, int y) const
    {
        return backend[y * dimension + x];
    }

    void move();

    bool nextPosValid(const int pos, bool wallValid = false) const;


    bool isGoal() const
    {
        return m_curr_pos == m_goal;
    }

    void moveDfs();
    void moveBfs();
    void moveAStar();
    std::vector<int> getUnvisitedNeighbors(int pos);

    void reset(MOVE_TYPE moveType)
    {
        set_move_type(moveType);

        reset();
    }

    void reset();

    int calculateManhattanDistance(int pos) const;
};


#endif //MAZE_H
