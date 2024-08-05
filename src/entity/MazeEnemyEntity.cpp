//
// Created by GT3CH1 on 8/4/24.
//

#include "MazeEnemyEntity.h"

#include <stack>

#include "Maze.h"

void MazeEnemyEntity::onTick()
{
  // find player via DFS and track path
  auto path = findPathToPlayer();
  // move to player

  // CHOICE: Do nothing, go the WRONG way, or go the RIGHT way
  // rng

  switch (random() % 10)
  {
  case 1:
    {
      for (auto direction : {NORTH,SOUTH,EAST,WEST})
      {
        if (EntityManager::canMove(getPos(), direction))
        {
          setPos(move(direction));
          break;
        }
      }
      break;
    }
  default:
    {
      if (!path.empty())
      {
        const auto nextNode = path.back();
        path.pop_back();
        setPos(nextNode->getPos());
      }
      break;
    }
  }
}

std::vector<MazeNode *> MazeEnemyEntity::findPathToPlayer() const
{
  std::vector<MazeNode *> path;
  std::set<MazeNode *> visited;
  std::stack<MazeNode *> stack;
  const auto m_node = Maze::get(getPos());
  stack.push(m_node);
  while (!stack.empty())
  {
    auto node = stack.top();
    stack.pop();

    if (node->getPos() == Maze::getPlayer()->getPos())
    {
      // found player
      // reconstruct path
      while (node != m_node)
      {
        path.push_back(node);
        node = node->getParent();
      }
      break;
    }
    visited.insert(node);
    for (auto neighbor : Maze::getNeighbors(node))
    {
      // if neighbor is not in visited set
      if (visited.find(neighbor) == visited.end())
      {
        neighbor->setParent(node);
        stack.push(neighbor);
      }
    }
  }

  return path;
}
