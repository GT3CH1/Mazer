//
// Created by GT3CH1 on 8/4/24.
//

#ifndef MAZEGOALENTITY_H
#define MAZEGOALENTITY_H

#include "MazeEntity.h"

class MazeGoalEntity : public MazeEntity
{
  public:
  explicit MazeGoalEntity(const Point position, const Color color = Color(GREEN)) : MazeEntity(position, GOAL, color) {}
};


#endif // MAZEGOALENTITY_H
