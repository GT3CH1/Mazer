//
// Created by GT3CH1 on 7/23/24.
//

#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include "EntityManager.h"
#include "MazeGenerator.h"
#include "MazeNode.h"
#include "Solver.h"
#include "types.h"

class Maze
{
  static Point m_start;
  int m_seed{};
  Solver solver = Solver(Djikstra);
  static std::vector<MazeNode *> *m_nodes;
  static Size m_size;
  static EntityManager entityManager;
  
  // static Maze* instance;
  MazeGenerator generator;

  static std::vector<bool> visited;

  public:
  Maze(Size size, Point start);
  [[nodiscard]] static int getDimension() { return m_size.area(); }
  [[nodiscard]] static bool playerSolved();
  static void generate(bool iterative = false);
  static MazeNode *getEnd() { return get(entityManager.getGoal()->getPos()); }
  static MazeNode *getStart() { return get(entityManager.getPlayer()->getPos()); }

  static std::stack<MazeNode *> generationStack;

  [[nodiscard]] static MazeNode *get(const Point point)
  {
    // validate pos
    if (point.getX() >= 0 && point.getX() < m_size.x && point.getY() >= 0 && point.getY() < m_size.y)
      return get(point.getX(), point.getY());
    return nullptr;
  }

  [[nodiscard]] static MazeNode *get(const int x, const int y)
  {
    if (x < 0 || x >= m_size.x || y < 0 || y >= m_size.y)
      return nullptr;
    if (!m_nodes)
    {
      return nullptr;
    }
    return m_nodes->at(y * m_size.x + x);
  }

  static std::vector<MazeNode*>* getNodes() { return m_nodes; }

  static int getDistanceToGoal(const MazeNode *node);
  static void movePlayer(Direction direction);
  std::set<MazeNode *> getVisitedNodes();
  static bool solved();
  static int getSize() { return m_size.x; }

  void reset(SolveType solveType);
  void reset();
  void setSolveType(SolveType type);
  static MazePlayerEntity *getPlayer() { return entityManager.getPlayer(); }
  void doSolveMove()
  {
    if (!solved())
      solver.doMove();
  }

  static void generationReset()
  {
    // reset all walls on all nodes

    for (const auto node : *m_nodes)
    {
      node->resetWalls();
    }
    while (!generationStack.empty())
      generationStack.pop();
    visited = std::vector<bool>(m_size.area(), false);
    generationStack.push(get(m_start));
  }

  static EntityManager *getEntityManager() { return &entityManager; }

  static std::vector<MazeNode *> getNeighbors(const MazeNode *node);
};


#endif // MAZE_H
