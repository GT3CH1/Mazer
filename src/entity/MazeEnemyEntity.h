//
// Created by GT3CH1 on 8/4/24.
//

#ifndef MAZEENEMYENTITY_H
#define MAZEENEMYENTITY_H
#include "MazeEntity.h"
#include "types.h"

class MazeEnemyEntity : public MazeEntity
{
  private:
  std::vector<MazeNode *> findPathToPlayer() const;

  public:
  explicit MazeEnemyEntity(const Point position, const Color color = Color(RED)) : MazeEntity(position, ENEMY, color) {}
  void onTick() override;
};


#endif // MAZEENEMYENTITY_H
