#include <iostream>
#include <SDL2/SDL.h>

#include "maze.h"

int main()
{
    srandom(time(nullptr));

    // Initialize SDL
    auto theMaze = maze(50, 0, A_STAR);
    // theMaze.
    const auto dimension = theMaze.getDimension();
    const auto pixelSize = 500 / dimension;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // Create a window
    SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 500, 500, SDL_WINDOW_SHOWN);
    // Create a renderer
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // while escape key is not pressed
    SDL_Event e;
    bool quit = false;
    bool firstTick = true;
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
                if (e.key.keysym.sym == SDLK_a)
                {
                    theMaze.reset(A_STAR);
                }
                if (e.key.keysym.sym == SDLK_b)
                {
                    theMaze.reset(BFS);
                }
                if (e.key.keysym.sym == SDLK_d)
                {
                    theMaze.reset(DFS);
                }
                if (e.key.keysym.sym == SDLK_r)
                {
                    theMaze = maze(50, 0, theMaze.get_move_type());
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
                SDL_Rect rect = {i * pixelSize, j * pixelSize, pixelSize, pixelSize};
                switch (theMaze.get(i, j))
                {
                case GOAL:
                    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
                    break;
                case EMPTY:
                    SDL_SetRenderDrawColor(ren, 50, 50, 50, 255);
                    break;
                case START:
                    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
                    break;
                case VISITED:
                    SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
                    break;
                case ACTIVE:
                    SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);
                    break;
                case QUEUED:
                    SDL_SetRenderDrawColor(ren, 255, 0, 255, 255);
                    break;
                default:
                    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                    break;
                }

                SDL_RenderFillRect(ren, &rect);
                SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                SDL_RenderDrawRect(ren, &rect);
            }
        }

        // render the changes above
        // SDL_Delay(250);
        SDL_RenderPresent(ren);
    }

    return 0;
}
