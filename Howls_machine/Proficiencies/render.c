#include "tic_tac_toe.h"
#include <err.h>
#include <SDL2/SDL.h>

void init_window(SDL_Window **window, SDL_Renderer **renderer)
{
    // 600 * 600
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        errx(1, "%s", SDL_GetError());
    
    }
    *window = SDL_CreateWindow("Tic-Tac-Toe",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,600,SDL_WINDOW_SHOWN);

       if (*window == NULL)
    {
        SDL_Quit();
        errx(1, "%s", SDL_GetError());
    }
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL)
    {
        SDL_DestroyWindow(*window);
        SDL_Quit();
        errx(1, "%s", SDL_GetError());
    }

    if (SDL_RenderSetLogicalSize(*renderer, 600, 600) != 0)
    {
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        errx(1, "%s", SDL_GetError());
    }
}

void terminate(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_board(SDL_Renderer *renderer)
{
    int w = 0;
    int h = 0;

    // il faut la taille logi
    SDL_RenderGetLogicalSize(renderer, &w, &h);

    if (w == 0 || h == 0)
    {
        SDL_GetRendererOutputSize(renderer, &w, &h);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 1; i < 3; i++)
    {
        int x = (w * i) / 3;
        int y = (h * i) / 3;

        // vertical x, 0 a x, h
        SDL_RenderDrawLine(renderer, x, 0, x, h);
        // horizontal 0 Y a w y
        SDL_RenderDrawLine(renderer, 0, y, w, y);
    }
}

void draw_cross(SDL_Renderer *renderer, int row, int col)
{
    int w = 0;
    int h = 0;
    SDL_RenderGetLogicalSize(renderer, &w, &h);
    if (w == 0 || h == 0)
    {
        SDL_GetRendererOutputSize(renderer, &w, &h);
    }

    int cellw= w / 3;
    int cellh = h / 3;

    int padx = cellw/ 10;
    int pady = cellh / 10;

    int gauche = col * cellw+ padx;
    int dr = (col + 1) * cellw- padx;
    int top = row * cellh + pady;
    int btn= (row + 1) * cellh - pady;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    SDL_RenderDrawLine(renderer, gauche, top, dr, btn);

    SDL_RenderDrawLine(renderer, gauche, btn, dr, top);

}

void draw_square(SDL_Renderer *renderer, int row, int col)
{
    int w = 0;
    int h = 0;
    SDL_RenderGetLogicalSize(renderer, &w, &h);
    if (w == 0 || h == 0)
    {
        SDL_GetRendererOutputSize(renderer, &w, &h);
    }

    int cellw = w / 3;
    int cellh= h / 3;

    int padx = cellw / 10;
    int pady= cellh/ 10;

    SDL_Rect rect;
    rect.x = col * cellw + padx;
    rect.y = row * cellh+ pady;
    rect.w = cellw - 2 * padx;
    rect.h = cellh- 2 * pady;

    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);

    SDL_RenderDrawRect(renderer, &rect);

}

void draw_marks(SDL_Renderer *renderer, int board[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] == 1)
            {
                draw_cross(renderer, row, col);
            }
            else if (board[row][col] == 2)
            {
                draw_square(renderer, row, col);
            }
        }
    }
}
