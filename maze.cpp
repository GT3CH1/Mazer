//
// Created by GT3CH1 on 7/23/24.
//

#include "maze.h"

void maze::move()
{
    switch (m_move_type)
    {
    case BFS:
        moveBfs();
        break;
    case A_STAR:
        moveAStar();
        break;
    default:
        moveDfs();
        break;
    }
}

void maze::moveAStar()
{
    m_curr_pos = m_priority_queue.top().getPos();
    if (m_priority_queue.empty())
        return;
    m_priority_queue.pop();
    backend[m_curr_pos] = ACTIVE;
    if (nextPosValid(m_curr_pos - dimension))
    {
        m_priority_queue.emplace(m_curr_pos - dimension, calculateManhattanDistance(m_curr_pos - dimension));
        backend[m_curr_pos - dimension] = VISITED;
    }
    if (nextPosValid(m_curr_pos + dimension))
    {
        m_priority_queue.emplace(
            m_curr_pos + dimension,
            calculateManhattanDistance(m_curr_pos + dimension));
        backend[m_curr_pos + dimension] = VISITED;
    }
    if (nextPosValid(m_curr_pos - 1))
    {
        m_priority_queue.emplace(m_curr_pos - 1, calculateManhattanDistance(m_curr_pos - 1));
        backend[m_curr_pos - 1] = VISITED;
    }
    if (nextPosValid(m_curr_pos + 1))
    {
        m_priority_queue.emplace(m_curr_pos + 1, calculateManhattanDistance(m_curr_pos + 1));
        backend[m_curr_pos + 1] = VISITED;
    }
}

int maze::calculateManhattanDistance(int pos) const
{
    // calculate the manhattan distance between the current position and the goal
    int x1 = pos % dimension;
    int y1 = pos / dimension;
    int x2 = m_goal % dimension;
    int y2 = m_goal / dimension;
    return abs(x1 - x2) + abs(y1 - y2);
}


void maze::moveBfs()
{
    m_curr_pos = m_queue.front();
    m_queue.pop();
    backend[m_curr_pos] = ACTIVE;
    if (nextPosValid(m_curr_pos - dimension))
    {
        m_queue.push(m_curr_pos - dimension);
        backend[m_curr_pos - dimension] = VISITED;
    }
    if (nextPosValid(m_curr_pos + dimension))
    {
        m_queue.push(m_curr_pos + dimension);
        backend[m_curr_pos + dimension] = VISITED;
    }
    if (nextPosValid(m_curr_pos - 1))
    {
        m_queue.push(m_curr_pos - 1);
        backend[m_curr_pos - 1] = VISITED;
    }
    if (nextPosValid(m_curr_pos + 1))
    {
        m_queue.push(m_curr_pos + 1);
        backend[m_curr_pos + 1] = VISITED;
    }
}


void maze::moveDfs()
{
    if (m_stack.empty())
        return;
    // direction preferences: up -> down -> left -> right
    int pos = m_curr_pos;
    backend[m_curr_pos] = ACTIVE;
    // right
    if (nextPosValid(m_curr_pos + 1))
    {
        pos = m_curr_pos + 1;
    }
    // down
    else if (nextPosValid(m_curr_pos + dimension))
    {
        pos = m_curr_pos + dimension;
    }
    //left
    else if (nextPosValid(m_curr_pos - 1))
    {
        pos = m_curr_pos - 1;
    }
    //up
    else if (nextPosValid(m_curr_pos - dimension))
    {
        pos = m_curr_pos - dimension;
    }


    if (m_curr_pos != pos)
    {
        m_curr_pos = pos;
        backend[pos] = QUEUED;
        m_stack.push(m_curr_pos);
        return;
    }
    backend[m_curr_pos] = VISITED;
    // backtrack if no valid moves
    if (!m_stack.empty())
    {
        m_stack.pop();
        if (!m_stack.empty())
        {
            m_curr_pos = m_stack.top();
            backend[m_curr_pos] = ACTIVE;
        }
    }
}

bool maze::nextPosValid(const int pos, bool wallValid) const
{
    if (pos < 0 || pos >= dimension * dimension)
        return false;
    // check if pos along the left edge
    if (m_curr_pos % dimension == 0 && pos == m_curr_pos - 1)
    {
        return false;
    }
    // check if pos along the right edge
    if (m_curr_pos % dimension == dimension - 1 && pos == m_curr_pos + 1)
    {
        return false;
    }
    // check if pos along the top edge
    if (m_curr_pos < dimension && pos == m_curr_pos - dimension)
    {
        return false;
    }
    // check if pos along the bottom edge
    if (m_curr_pos >= dimension * (dimension - 1) && pos == m_curr_pos + dimension)
    {
        return false;
    }

    // check if next position is a wall or visited
    auto valid = backend[pos] == EMPTY || backend[pos] == GOAL || backend[pos] == START;
    if (wallValid)
        valid = valid || backend[pos] == WALL;
    return valid;
}

bool maze::hasSolution() const
{
    // in place A-Star to check if there is a solution
    std::priority_queue<AStarNode> q;
    q.emplace(m_start, calculateManhattanDistance(m_start));
    std::vector<bool> visited(dimension * dimension, false);
    while (!q.empty())
    {
        auto curr = q.top();
        q.pop();
        if (curr.getPos() == m_goal)
            return true;
        visited[curr.getPos()] = true;
        if (nextPosValid(curr.getPos() - dimension) && !visited[curr.getPos() - dimension])
        {
            q.emplace(curr.getPos() - dimension, calculateManhattanDistance(curr.getPos() - dimension));
        }
        if (nextPosValid(curr.getPos() + dimension) && !visited[curr.getPos() + dimension])
        {
            q.emplace(curr.getPos() + dimension, calculateManhattanDistance(curr.getPos() + dimension));
        }
        if (nextPosValid(curr.getPos() - 1) && !visited[curr.getPos() - 1])
        {
            q.emplace(curr.getPos() - 1, calculateManhattanDistance(curr.getPos() - 1));
        }
        if (nextPosValid(curr.getPos() + 1) && !visited[curr.getPos() + 1])
        {
            q.emplace(curr.getPos() + 1, calculateManhattanDistance(curr.getPos() + 1));
        }
    }
    return false;
}


void maze::reset()
{
    m_curr_pos = m_start;
    m_queue = std::queue<int>();
    m_queue.push(m_start);
    m_stack = std::stack<int>();
    m_stack.push(m_start);
    m_priority_queue = std::priority_queue<AStarNode>();
    m_priority_queue.emplace(m_start, calculateManhattanDistance(m_start));

    // set_move_type(moveType);
    for (int i = 0; i < dimension * dimension; i++)
    {
        if (backend[i] == VISITED || backend[i] == ACTIVE || backend[i] == QUEUED)
        {
            backend[i] = EMPTY;
        }
    }
}

void maze::initialize_map(int)
{
    backend = std::vector<int>(dimension * dimension);
    std::cout << "Initializing map" << std::endl;
    backend[m_goal] = GOAL;
    auto generation_stack = std::stack<int>();
    generation_stack.push(m_start);
    backend[m_start] = VISITED;
    while (!generation_stack.empty())
    {
        auto pos = generation_stack.top();
        generation_stack.pop();
        backend[pos] = ACTIVE;
        // check if any unvisited neighbors
        auto neighbors = getUnvisitedNeighbors(pos);
        if (!neighbors.empty())
        {
            generation_stack.push(pos);
            auto next = neighbors[random() % neighbors.size()];
            backend[next] = VISITED;
            generation_stack.push(next);
        }
        else
        {
            backend[pos] = VISITED;
        }
    }
    backend[m_start] = START;
    backend[m_goal] = GOAL;
    // for (int i = 0; i < dimension * dimension; i++)
    // {
    //     if (backend[i] == VISITED || backend[i] == ACTIVE)
    //     {
    //         backend[i] = EMPTY;
    //     }
    // }
}


std::vector<int> maze::getUnvisitedNeighbors(int pos)
{
    auto neighbors = std::vector<int>();
    if (nextPosValid(pos - 1, true))
    {
        neighbors.push_back(pos - 1);
    }
    if (nextPosValid(pos + 1, true))
    {
        neighbors.push_back(pos + 1);
    }
    if (nextPosValid(pos - dimension, true))
    {
        neighbors.push_back(pos - dimension);
    }
    if (nextPosValid(pos + dimension, true))
    {
        neighbors.push_back(pos + dimension);
    }

    return neighbors;
}
