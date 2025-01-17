//
// Created by GT3CH1 on 7/23/24.
//

#include "Maze.h"
// static Maze::instance = nullptr;
std::vector<MazeNode *> *Maze::m_nodes = new std::vector<MazeNode *>();
Size Maze::m_size = Size();
std::vector<bool> Maze::visited = std::vector<bool>();
Point Maze::m_start = Point();
EntityManager Maze::entityManager;
bool Maze::playerSolved() { return getPlayer()->getPos() == entityManager.getGoal()->getPos(); }


Maze::Maze(const Size size, const Point start) : generator(MazeGenerator(size, start, Point(size.x - 1, size.y - 1)))
{
  m_size = size;
  m_start = start;
  m_nodes = MazeGenerator::getMap();
  getEntityManager()->getGoal()->setPos(Point(m_size.x - 1, m_size.y - 1));
}


int Maze::getDistanceToGoal(const MazeNode *node)
{
  // get manhattan distance to goal
  const auto goal = get(entityManager.getGoal()->getPos());
  const auto distance =
      abs(node->getPos().getX() - goal->getPos().getX()) + abs(node->getPos().getY() - goal->getPos().getY());
  return distance;
}

void Maze::generate(const bool iterative)
{
  MazeGenerator::generationTick(iterative);

  m_nodes = MazeGenerator::getMap();
}

void Maze::movePlayer(const Direction direction)
{
  // const auto getPlayer() = get(entityManager.getPlayer()->getPos());
  const auto nodeAtPlayer = get(getPlayer()->getPos());
  if (nodeAtPlayer == nullptr)
    return;
  if (nodeAtPlayer->hasWall(direction))
    return;
  entityManager.getPlayer()->setPos(entityManager.getPlayer()->move(direction));
}

std::set<MazeNode *> Maze::getVisitedNodes() { return solver.getVisitedNodes(); }

bool Maze::solved()
{
  // check if the goal node has been visited
  return get(entityManager.getGoal()->getPos())->isVisited();
}

void Maze::reset(const SolveType solveType)
{
  setSolveType(solveType);
  reset();
}

void Maze::reset()
{
  for (const auto &node : *m_nodes)
  {
    node->reset();
  }
  visited.clear();
  solver.clear();
  solver.push(get(entityManager.getPlayer()->getPos()));
  entityManager.setPlayerPos(m_start);
  getEntityManager()->getGoal()->setPos(Point(m_size.x - 1, m_size.y - 1));
}

void Maze::setSolveType(const SolveType type) { solver.setSolveType(type); }

std::vector<MazeNode *> Maze::getNeighbors(const MazeNode *node)
{
  auto neighbors = std::vector<MazeNode *>();
  for (const auto direction : {NORTH, SOUTH, WEST, EAST})
  {
    auto loc = node->move(direction);
    if (auto neighbor = get(loc.getX(), loc.getY()); neighbor != nullptr && !node->hasWall(direction))
    {
      neighbors.push_back(neighbor);
    }
  }
  return neighbors;
}
