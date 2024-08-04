//
// Created by GT3CH1 on 7/24/24.
//

#ifndef MAZENODE_H
#define MAZENODE_H
#include <cstdint>

#include "MazeWall.h"
#include "types.h"

/**
 * A class representing a single node (square) in a maze.
 */
class MazeNode
{
  public:
  /**
   * Create a new MazeNode at the given position.
   * @param point The position of the node in the maze.
   */
  explicit MazeNode(const Point point) : m_pos(point) {}


  /**
   * Creates a new MazeNode at the origin (0, 0).
   */
  MazeNode() : MazeNode(Point(0, 0)) {}

  /**
   * Sets the position of the node.
   * @param pos The new position of the node.
   */
  void setPos(Point pos);

  /**
   * Gets the position of the node.
   * @return The position of the node.
   */
  [[nodiscard]] Point getPos() const;

  /**
   * Gets the position of the node above this one.
   * @return The position of the node above this one.
   */
  [[nodiscard]] Point up() const;

  /**
   * Gets the position of the node below this one.
   * @return The position of the node below this one.
   */
  [[nodiscard]] Point down() const;

  /**
   * Gets the position of the node to the left of this one.
   * @return The position of the node to the left of this one.
   */
  [[nodiscard]] Point left() const;

  /**
   * Gets the position of the node to the right of this one.
   * @return The position of the node to the right of this one.
   */
  [[nodiscard]] Point right() const;

  /**
   * Moves the node in the given direction.
   * @param direction The direction to move the node.
   * @return The new position of the node.
   */
  [[nodiscard]] Point move(Direction direction) const;

  /**
   * Gets the direction to a neighboring node.
   * @param node The node to get the direction to.
   * @return The direction to the neighboring node.
   */
  [[nodiscard]] Direction getDirectionToNeighbor(const MazeNode *node) const;

  /**
   * Resets the node to its initial state.
   */
  void reset();

  /**
   * Resets the walls of the node.
   */
  void resetWalls();

  /**
   * Checks if the node has the given wall.
   * @param wall The MazeWall to check for.
   * @return True if the node has the wall, false otherwise.
   */
  [[nodiscard]] bool hasWall(MazeWall::MazeWall wall) const;

  /**
   * Checks if the node has a wall in the given direction.
   * @param direction The direction to check for a wall.
   * @return True if the node has a wall in the given direction, false otherwise.
   */
  [[nodiscard]] bool hasWall(Direction direction) const;

  /**
   * Sets the wall of the node.
   * @param wall The wall to set.
   */
  void setWall(MazeWall::MazeWall wall);

  /**
   * Sets the wall for the node.
   * @param wall The wall to set.
   */
  void clearWall(MazeWall::MazeWall wall);

  /**
   * Clears all walls of the node.
   */
  void clearAllWalls();

  /**
   * Whether the position of the node is valid.
   * @return True if the position is valid, false otherwise.
   */
  [[nodiscard]] bool posValid() const;

  /**
   * Marks this node as visited.
   */
  void visit();

  /**
   * Marks this node as active.
   */
  void setActive();
  /**
   * Whether the node is active.
   * @return  True if the node is active, false otherwise.
   */
  [[nodiscard]] bool isActive() const;

  /**
   * Gets whether this node is visited.
   * @return Whether this node is visited.
   */
  [[nodiscard]] bool isVisited() const;

  /**
   * Clears the wall between this node and the given neighbor.
   * @param direction The direction of the neighbor.
   * @param neighbor The neighbor to remove the wall with.
   */
  void removeWall(Direction direction, MazeNode *neighbor);

  /**
   * Removes the wall in the given direction.
   * @param direction The direction to remove the wall.
   */
  void removeWall(Direction direction);

  bool operator<(const MazeNode &rhs) const { return m_pos < rhs.m_pos; }

  bool operator>(const MazeNode &rhs) const { return rhs < *this; }


  void setGoal() { m_isGoal = true; }
  [[nodiscard]] bool isGoal() const { return m_isGoal; }

  void setStart() { m_isStart = true; }
  [[nodiscard]] bool isStart() const { return m_isStart; }

  private:
  uint8_t m_walls = MazeWall::ALL;
  Point m_pos;
  bool m_visited = false;
  bool m_isGoal = false;
  bool m_isStart = false;
  bool m_isActive = false;
};


#endif // MAZENODE_H
