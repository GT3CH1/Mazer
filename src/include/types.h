//
// Created by GT3CH1 on 7/24/24.
//

#ifndef TYPES_H
#define TYPES_H
#include <random>
/**
 * An enum that represents a direction..
 */
enum Direction
{
  NORTH = 0,
  EAST,
  SOUTH,
  WEST
};

static Direction getRandomDirection() { return static_cast<Direction>(random() % 4); }

/**
 * A class that represents a size in 2D space.
 */
class Size
{
  public:
  explicit Size(const int width = 0, const int height = 0) : x(width), y(height) {}

  int x;
  int y;
  [[nodiscard]] int area() const { return x * y; }
};

/**
 * A class that represents a point in 2D space.
 */
class Point
{
  public:
  Point() : x(0), y(0) {}

  Point(const int x, const int y) : x(x), y(y) {}

  [[nodiscard]] int getX() const { return x; }
  [[nodiscard]] int getY() const { return y; }
  bool operator==(const Point &other) const { return x == other.x && y == other.y; }

  bool operator>(const Point &other) const
  {
    // calculate manhattan distance
    return x > other.x && y > other.y;
  }

  bool operator<(const Point &other) const { return x < other.x && y < other.y; }
  bool operator>=(const Point &other) const { return x >= other.x && y >= other.y; }
  static Point getRandom(Size size)
  {
    return {static_cast<int>(random()) % size.x, static_cast<int>(random()) % size.y};
  }

  private:
  int x;
  int y;
};

enum Colors
{
  RED = 0xFF0000FF,
  GREEN = 0x00FF00FF,
  BLUE = 0x0000FFFF,
  WHITE = 0xFFFFFFFF,
  BLACK = 0x000000FF,
  GRAY = 0x808080FF,
  PURPLE = 0x800080FF
};

/**
 * @brief A class that represents a color.
 * The color is stored as a 32-bit unsigned integer.
 */
class Color
{
  /**
   * A color. |r|g|b|a| 8-bit values
   */
  uint32_t color;

  public:
  /**
   * Creates a color from a 32-bit unsigned integer.
   * @param color The color as a 32-bit unsigned integer.
   */
  explicit Color(const uint32_t color) { this->color = color; }

  /**
   * Creates a color from a Colors enum.
   * @param color The color as a Colors enum.
   * @see Colors
   */
  explicit Color(const Colors color) : Color(static_cast<uint32_t>(color)) {}

  /**
   * Creates a color from 4 8-bit values.
   * @param r The red value.
   * @param g The green value.
   * @param b The blue value.
   * @param a The alpha value.
   */
  Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) : Color(r << 24 | g << 16 | b << 8 | a) {}

  /**
   * Creates a color from 3 8-bit values.
   * @param r The red value.
   * @param g The green value.
   * @param b The blue value.
   */
  Color(const uint8_t r, const uint8_t g, const uint8_t b) : Color(r, g, b, 255) {}


  /**
   * Gets the red value of the color.
   * @return The red value.
   */
  [[nodiscard]] uint8_t getRed() const { return (color >> 24) & 0xFF; }

  /**
   * Gets the green value of the color.
   * @return The green value.
   */
  [[nodiscard]] uint8_t getGreen() const { return (color >> 16) & 0xFF; }

  /**
   * Gets the blue value of the color.
   * @return The blue value.
   */
  [[nodiscard]] uint8_t getBlue() const { return (color >> 8) & 0xFF; }

  /**
   * Gets the alpha value of the color.
   * @return The alpha value.
   */
  [[nodiscard]] uint8_t getAlpha() const { return color & 0xFF; }

  /**
   * Gets the color as a 32-bit unsigned integer.
   * @return The color as a 32-bit unsigned integer.
   */
  [[nodiscard]] uint32_t getColor() const { return color; }

  /**
   * Sets the red value of the color.
   * @param r The red value.
   */
  void setRed(const uint8_t r) { color = (color & 0x00FFFFFF) | (r << 24); }

  /**
   * Sets the green value of the color.
   * @param g The green value.
   */
  void setGreen(const uint8_t g) { color = (color & 0xFF00FFFF) | (g << 16); }

  /**
   * Sets the blue value of the color.
   * @param b The blue value.
   */
  void setBlue(const uint8_t b) { color = (color & 0xFFFF00FF) | (b << 8); }

  /**
   * Sets the alpha value of the color.
   * @param a The alpha value.
   */
  void setAlpha(const uint8_t a) { color = (color & 0xFFFFFF00) | a; }
};

enum MazeEntityType
{
  PLAYER,
  GOAL,
  ENEMY,
  NODE
};

#endif // TYPES_H
