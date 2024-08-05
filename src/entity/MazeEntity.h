//
// Created by GT3CH1 on 8/4/24.
//

#ifndef MAZEENTITY_H
#define MAZEENTITY_H

#include <SDL2/SDL.h>


#include "MazeNode.h"
#include "types.h"

/**
 * A MazeEntity is a base class for all entities in the maze.
 */
class MazeEntity : public MazeNode
{
  // The static id counter
  static uint32_t s_idCounter;

  // The color of the entity
  Color m_color;

  // The unique id of the entity
  uint32_t m_id;

  MazeEntityType m_type;

  public:
  explicit MazeEntity(const Point position, const MazeEntityType entityType = NODE, const Color color = Color(WHITE)) :
      m_color(color), m_type(entityType)
  {
    setPos(position);
    m_id = s_idCounter++;
  }

  bool operator==(const MazeEntity &rhs) const { return m_id == rhs.m_id; }

  [[nodiscard]] Color *getColor() { return &m_color; }

  void render(SDL_Renderer *renderer, int pixelSize) const;

  virtual void onTick(){};
};


#endif // MAZEENTITY_H
