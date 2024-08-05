//
// Created by GT3CH1 on 8/4/24.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include "MazeEnemyEntity.h"
#include "MazeEntity.h"
#include "MazeGoalEntity.h"
#include "MazePlayerEntity.h"

class EntityManager
{
  private:
  std::vector<MazeEntity *> nodes;
  int m_nodeCount;
  int m_nextNodeIndex = 0;
  Size m_size;

  MazePlayerEntity *m_player = nullptr;
  MazeGoalEntity *m_goal = nullptr;

  /**
   * Finds the next available node index
   * @return the next available node index, or -1 if no node is available
   */
  [[nodiscard]] int findNextNodeIndex() const;

  public:
  explicit EntityManager(int nodeCount, Size size);
  EntityManager() : EntityManager(100, Size(15, 15)) {}
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

  [[nodiscard]] MazeGoalEntity *getGoal() const { return m_goal; }

  void setPlayerPos(const Point pos) const { m_player->setPos(pos); }

  void render(SDL_Renderer *ren, int pixelSize) const;
  void onTick() const;
  static bool canMove(Point pos, Direction direction);
};


#endif // ENTITYMANAGER_H
