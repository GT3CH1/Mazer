//
// Created by GT3CH1 on 8/4/24.
//

#include "EntityManager.h"
#include "Maze.h"


int EntityManager::findNextNodeIndex() const
{
  for (int i = 0; i < m_nodeCount; i++)
  {
    if (nodes[i] == nullptr)
    {
      return i;
    }
  }
  return -1;
}

EntityManager::EntityManager(const int nodeCount, const Size size)
{
  m_size = size;
  m_nodeCount = nodeCount;
  m_nextNodeIndex = 0;
  nodes.reserve(m_nodeCount);
  for (int i = 0; i < m_nodeCount; i++)
  {
    nodes.push_back(nullptr);
  }
  m_player = new MazePlayerEntity(Point(0, 0));
  const auto enemy = new MazeEnemyEntity(Point::getRandom(size));
  const auto goal = new MazeGoalEntity(Point(size.x - 1, size.y - 1));
  m_goal = goal;
  addNode(m_player);
  addNode(enemy);
  addNode(goal);
}

EntityManager::~EntityManager()
{
  // free memory for nodes
  for (const auto node : nodes)
  {
    delete node;
  }
}

void EntityManager::addNode(MazeEntity *node)
{
  nodes[m_nextNodeIndex] = node;
  m_nextNodeIndex = findNextNodeIndex();
}
void EntityManager::removeNode(const MazeEntity *node)
{
  // find node in nodes
  for (int i = 0; i < m_nodeCount; i++)
  {
    if (nodes[i] == node)
    {
      nodes[i] = nullptr;
      m_nextNodeIndex = i;
      return;
    }
  }
}
MazePlayerEntity *EntityManager::getPlayer() const { return m_player; }
void EntityManager::render(SDL_Renderer *ren, const int pixelSize) const
{
  // m_player->render(ren, pixelSize);
  // render nodes
  for (const auto node : nodes)
  {
    if (node != nullptr)
    {
      node->render(ren, pixelSize);
    }
  }
}
void EntityManager::onTick() const
{
  for (const auto node : nodes)
  {
    if (node != nullptr)
    {
      node->onTick();
    }
  }
}
bool EntityManager::canMove(const Point pos, const Direction direction)
{
  // check if the next position is in bounds
  if (pos.getX() < 0 || pos.getX() >= Maze::getSize() || pos.getY() < 0 || pos.getY() >= Maze::getSize())
  {
    return false;
  }
  // check if the next position is a wall
  const auto node = Maze::get(pos);
  if (node == nullptr)
  {
    return false;
  }
  return !node->hasWall(direction);
}
