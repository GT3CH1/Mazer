//
// Created by GT3CH1 on 8/4/24.
//

#include "EntityManager.h"

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

EntityManager::EntityManager(const int nodeCount)
{
  m_nodeCount = nodeCount;
  m_nextNodeIndex = 0;
  nodes.reserve(m_nodeCount);
  for (int i = 0; i < m_nodeCount; i++)
  {
    nodes.push_back(nullptr);
  }
  m_player = new MazePlayerEntity(Point(0, 0));
  // addNode(m_player);
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
