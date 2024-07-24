#include <iostream>
#include <SDL2/SDL.h>

#include "Maze.h"

int main()
{
    srandom(time(nullptr));

    auto theMaze = Maze(Size(20, 20), Point(0, 0), Point(19, 19), 0);
    const auto dimension = theMaze.getSize();
    const auto pixelSize = 500 / dimension;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // Create a window
    SDL_Window* win = SDL_CreateWindow("Mazer", 100, 100, 500, 500, SDL_WINDOW_SHOWN);
    // Create a renderer
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // while escape key is not pressed
    SDL_Event e;
    bool quit = false;
    bool firstTick = true;
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
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
        }
        // draw a white background
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);
        // for each cell in the maze, draw a black rectangle


        // if (!firstTick && !theMaze.isGoal())
        //     theMaze.move();
        firstTick = false;
        for (int i = 0; i < theMaze.getDimension(); i++)
        {
            for (int j = 0; j < theMaze.getDimension(); j++)
            {
                auto node = theMaze.get(i, j);
                // draw walls for each cell
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
                if (node->isGoal())
                {
                    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
                    SDL_RenderFillRect(ren, new SDL_Rect{i * pixelSize, j * pixelSize, pixelSize, pixelSize});
                }
            }
        }

        // render the changes above
        // SDL_Delay(250);
        SDL_RenderPresent(ren);
    }

    return 0;
}
