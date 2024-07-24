#include <iostream>
#include <SDL2/SDL.h>

#include "Maze.h"

int main()
{
    srandom(time(nullptr));

    auto theMaze = Maze(Size(55, 55), Point(0, 0), Point(54, 54), 0);
    const auto dimension = Maze::getSize();
    const auto pixelSize = 800 / dimension;

    // Initialize DL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // Create a window
    SDL_Window* win = SDL_CreateWindow("Mazer", 100, 100, pixelSize*dimension, pixelSize*dimension, SDL_WINDOW_SHOWN);
    // Create a renderer
    //SDL_RENDERER_PRESENTVSYNC
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // while escape key is not pressed
    SDL_Event e;
    bool quit = false;
    bool firstTick = true;
    bool draw = true;
    bool pause = false;
    // theMaze.get(0, 0)->clearAllWalls();
    // theMaze.get(1, 0)->clearAllWalls();
    while (!quit)
    {
        // check for events
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_f:
                    theMaze.reset(Djikstra);
                    break;
                case SDLK_b:
                    theMaze.reset(BFS);
                    break;
                case SDLK_d:
                    theMaze.reset(DFS);
                    break;
                case SDLK_r:
                    theMaze.reset();
                    break;
                case SDLK_n:
                    theMaze.reset();
                    theMaze.generate();
                    break;
                case SDLK_SPACE:
                    pause = !pause;
                    break;
                case SDLK_s:
                    draw = !draw;
                    break;
                default:
                    break;
                }
            }
        }
        // draw a white background
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);
        // for each cell in the maze, draw a black rectangle


        if (!firstTick && !pause)
            theMaze.doSolveMove();
        firstTick = false;
        for (int i = 0; i < Maze::getDimension(); i++)
        {
            for (int j = 0; j < Maze::getDimension(); j++)
            {
                auto node = Maze::get(i, j);
                if (node == nullptr)
                    continue;
                // draw walls for each cell
                if (node->isVisited() && draw)
                {
                    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                    SDL_RenderFillRect(ren, new SDL_Rect{i * pixelSize, j * pixelSize, pixelSize, pixelSize});
                }
                if (node->isGoal())
                {
                    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
                    SDL_RenderFillRect(ren, new SDL_Rect{i * pixelSize, j * pixelSize, pixelSize, pixelSize});
                }
                if (node->isActive() && draw)
                {
                    SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);
                    SDL_RenderFillRect(ren, new SDL_Rect{i * pixelSize, j * pixelSize, pixelSize, pixelSize});
                }
                if (node->isStart())
                {
                    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
                    SDL_RenderFillRect(ren, new SDL_Rect{i * pixelSize, j * pixelSize, pixelSize, pixelSize});
                }

                if (node->hasWall(MazeWall::NORTH))
                {
                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                    SDL_RenderDrawLine(ren, i * pixelSize, j * pixelSize, (i + 1) * pixelSize, j * pixelSize);
                }
                if (node->hasWall(MazeWall::EAST))
                {
                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                    SDL_RenderDrawLine(ren, (i + 1) * pixelSize, j * pixelSize, (i + 1) * pixelSize,
                                       (j + 1) * pixelSize);
                }
                if (node->hasWall(MazeWall::SOUTH))
                {
                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                    SDL_RenderDrawLine(ren, i * pixelSize, (j + 1) * pixelSize, (i + 1) * pixelSize,
                                       (j + 1) * pixelSize);
                }
                if (node->hasWall(MazeWall::WEST))
                {
                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                    SDL_RenderDrawLine(ren, i * pixelSize, j * pixelSize, i * pixelSize, (j + 1) * pixelSize);
                }
            }
        }

        SDL_RenderPresent(ren);
    }

    return 0;
}
