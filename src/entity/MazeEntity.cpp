//
// Created by GT3CH1 on 8/4/24.
//

#include "MazeEntity.h"

uint32_t MazeEntity::s_idCounter = 0;


void MazeEntity::render(SDL_Renderer *renderer, const int pixelSize) const
{
  const auto red = m_color.getRed();
  const auto green = m_color.getGreen();
  const auto blue = m_color.getBlue();
  const auto alpha = m_color.getAlpha();
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
  const auto x = getPos().getX();
  const auto y = getPos().getY();
  SDL_RenderDrawRect(renderer, new SDL_Rect{x * pixelSize, y * pixelSize, pixelSize, pixelSize});
}
