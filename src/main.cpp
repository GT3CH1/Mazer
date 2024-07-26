#include <iostream>
#include <SDL2/SDL.h>

#include "Maze.h"

void draw_walls(int dimension, int pixelSize, SDL_Renderer* ren, SDL_Texture*& texture);
int mazeSize = 5;

void draw_maze_nodes(Maze theMaze, int pixelSize, SDL_Renderer* ren, bool draw)
{
    for (const auto node : theMaze.getVisitedNodes())
    {
        const auto i = node->getPos().getX();
        const auto j = node->getPos().getY();
        // draw walls for each cell
        if (node->isVisited() && draw)
        {
            SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
            SDL_RenderFillRect(ren, new SDL_Rect{i * pixelSize, j * pixelSize, pixelSize, pixelSize});
        }

        if (node->isActive() && draw)
        {
            SDL_SetRenderDrawColor(ren, 0, 100, 100, 255);
            SDL_RenderFillRect(ren, new SDL_Rect{i * pixelSize, j * pixelSize, pixelSize, pixelSize});
        }
        if (node->isStart())
        {
            SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
            SDL_RenderFillRect(ren, new SDL_Rect{i * pixelSize, j * pixelSize, pixelSize, pixelSize});
        }
    }
}

void draw_start_end_nodes(const int pixelSize, SDL_Renderer* ren)
{
    auto node = Maze::getEnd();
    auto i = node->getPos().getX();
    auto j = node->getPos().getY();
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    SDL_RenderFillRect(ren, new SDL_Rect{i * pixelSize, j * pixelSize, pixelSize, pixelSize});

    node = Maze::getStart();
    i = node->getPos().getX();
    j = node->getPos().getY();
    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
    SDL_RenderFillRect(ren, new SDL_Rect{i * pixelSize, j * pixelSize, pixelSize, pixelSize});
}

int main()
{
    srandom(time(nullptr));

    auto theMaze = Maze(Size(mazeSize, mazeSize), Point(0, 0));
    auto dimension = Maze::getSize();
    auto pixelSize = 700 / dimension;
    // Initialize DL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // Create a window
    SDL_Window* win = SDL_CreateWindow("Mazer", 100, 100, pixelSize * dimension, pixelSize * dimension,
                                       SDL_WINDOW_SHOWN);
    // Create a renderer
    //SDL_RENDERER_PRESENTVSYNC
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // while escape key is not pressed
    SDL_Event e;
    bool quit = false;
    bool firstTick = true;
    bool draw = true;
    bool pause = true;
    bool showGeneration = true;
    SDL_Texture* texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 700, 700);

    draw_walls(dimension, pixelSize, ren, texture);
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
                    // theMaze.reset();
                    // Maze::generate();
                    MazeGenerator::reset();
                    Maze::generate(false);
                    draw_walls(dimension, pixelSize, ren, texture);
                    break;
                case SDLK_SPACE:
                    pause = !pause;
                    break;
                case SDLK_s:
                    draw = !draw;
                    break;
                case SDLK_UP:
                    theMaze.movePlayer(NORTH);
                    break;
                case SDLK_DOWN:
                    theMaze.movePlayer(SOUTH);
                    break;
                case SDLK_LEFT:
                    theMaze.movePlayer(WEST);
                    break;
                case SDLK_RIGHT:
                    theMaze.movePlayer(EAST);
                    break;
                case SDLK_g:
                    {
                        showGeneration = !showGeneration;
                        if (showGeneration)
                        {
                            SDL_RenderClear(ren);
                            MazeGenerator::reset();
                            Maze::generate(true);
                        }
                    }
                default:
                    break;
                }
            }
        }
        // draw a white background
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        // for each cell in the maze, draw a black rectangle
        if (!firstTick && !pause)
            theMaze.doSolveMove();
        if (showGeneration && !pause)
        {
            Maze::generate(true);
            SDL_RenderClear(ren);
            draw_walls(dimension, pixelSize, ren, texture);
            SDL_RenderCopy(ren, texture, nullptr, nullptr);
            // draw top of generation stack
            if (MazeGenerator::doneGenerating())
            {
                showGeneration = false;
                continue;
            }
            auto const node = MazeGenerator::getTop();
            if (node)
            {
                SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
                SDL_RenderFillRect(ren, new SDL_Rect{
                                       node->getPos().getX() * pixelSize, node->getPos().getY() * pixelSize, pixelSize,
                                       pixelSize
                                   });
            }
            SDL_RenderPresent(ren);
            continue;
        }
        if (theMaze.playerSolved())
        {
            mazeSize += 5;
            theMaze = Maze(Size(mazeSize, mazeSize), Point(0, 0));
            dimension = Maze::getSize();
            pixelSize = 700 / dimension;
            theMaze.generate();
            draw_walls(dimension, pixelSize, ren, texture);
        }
        firstTick = false;
        auto playerPos = theMaze.playerNode()->getPos();
        SDL_SetRenderDrawColor(ren, 255, 0, 255, 255);
        SDL_RenderFillRect(ren, new SDL_Rect{
                               playerPos.getX() * pixelSize, playerPos.getY() * pixelSize, pixelSize, pixelSize
                           });
        draw_maze_nodes(theMaze, pixelSize, ren, draw);
        draw_start_end_nodes(pixelSize, ren);

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderCopy(ren, texture, nullptr, nullptr);
        SDL_RenderPresent(ren);
    }
    return 0;
}

void draw_walls(const int dimension, const int pixelSize, SDL_Renderer* ren, SDL_Texture*& texture)
{
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);
    SDL_SetRenderTarget(ren, texture);
    SDL_RenderClear(ren);
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            const auto node = Maze::get(i, j);
            if (node == nullptr)
                continue;
            SDL_SetRenderDrawColor(ren, 75, 75, 75, 255);
            if (node->hasWall(MazeWall::NORTH))
            {
                SDL_RenderDrawLine(ren, i * pixelSize, j * pixelSize, (i + 1) * pixelSize, j * pixelSize);
            }
            if (node->hasWall(MazeWall::EAST))
            {
                SDL_RenderDrawLine(ren, (i + 1) * pixelSize, j * pixelSize, (i + 1) * pixelSize,
                                   (j + 1) * pixelSize);
            }
            if (node->hasWall(MazeWall::SOUTH))
            {
                SDL_RenderDrawLine(ren, i * pixelSize, (j + 1) * pixelSize, (i + 1) * pixelSize,
                                   (j + 1) * pixelSize);
            }
            if (node->hasWall(MazeWall::WEST))
            {
                SDL_RenderDrawLine(ren, i * pixelSize, j * pixelSize, i * pixelSize, (j + 1) * pixelSize);
            }
        }
    }
    SDL_SetRenderTarget(ren, nullptr);
}
