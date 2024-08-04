//
// Created by GT3CH1 on 8/4/24.
//

#ifndef MAZEPLAYERENTITY_H
#define MAZEPLAYERENTITY_H

#include "MazeEntity.h"

class MazePlayerEntity : public MazeEntity
{
  public:
  explicit MazePlayerEntity(const Point position, const Color color = Color(PURPLE)) :
      MazeEntity(position, PLAYER, color)
  {
  }
};


#endif // MAZEPLAYERENTITY_H
