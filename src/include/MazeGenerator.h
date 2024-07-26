//
// Created by GT3CH1 on 7/25/24.
//

#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H
#include "../maze/MazeNode.h"
#include <vector>
#include <stack>

class MazeGenerator
{
    static std::stack<MazeNode*> generationStack;
    static std::vector<bool> visited;
    static std::vector<MazeNode*>* map;
    static MazeNode* get(Point position);
    static MazeNode* get(int x, int y);
    static Size m_size;
    static void psuedorandomDfsTick();
    static Point m_start;
    static Point m_end;

public:
    explicit MazeGenerator(Size size, Point start, Point end);
    /**
     * Resets the maze generator
     */
    static void reset();

    /**
     * Performs a single tick of the psuedorandom depth first search algorithm used to
     * generate a maze.
     * If the iterative flag is set to true, the algorithm will generate the maze iteratively,
     * allowing the user to see the maze being generated in real time.
     * If the iterative flag is set to false, the algorithm will generate the maze in one go.
     */
    static std::vector<MazeNode*>* generationTick(bool iterative = false);

    /**
     * Returns the generated maze
     * @return the generated maze
     */
    [[nodiscard]] static std::vector<MazeNode*>* getMap() { return map; }

    /**
     * Whether the maze generation is done
     * @return true if the maze generation is done, false otherwise
     */
    static bool doneGenerating();

    /**
     *  Returns the top of the generation stack
     * @return the top of the generation stack
     */
    static MazeNode* getTop()
    {
        if (generationStack.empty())
            return nullptr;
        return generationStack.top();
    }
};


#endif //MAZEGENERATOR_H
