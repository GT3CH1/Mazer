//
// Created by GT3CH1 on 8/4/24.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include "MazeEntity.h"
#include "MazePlayerEntity.h"

class EntityManager
{
  private:
  std::vector<MazeEntity *> nodes;
  int m_nodeCount;
  int m_nextNodeIndex = 0;

  MazePlayerEntity *m_player = nullptr;

  /**
   * Finds the next available node index
   * @return the next available node index, or -1 if no node is available
   */
  [[nodiscard]] int findNextNodeIndex() const;

  public:
  explicit EntityManager(int nodeCount);
  ~EntityManager();

  /**
   * Adds a node to the entity manager
   * @param node the node to add
   */
  void addNode(MazeEntity *node);
  /**
   * Removes a node from the entity manager
   * @param node the node to remove
   */
  void removeNode(const MazeEntity *node);

  /**
   * Gets the player entity
   * @return
   */
  [[nodiscard]] MazePlayerEntity *getPlayer() const;

  void setPlayerPos(const Point pos) const { m_player->setPos(pos); }
};


#endif // ENTITYMANAGER_H
