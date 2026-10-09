#include <stdio.h>
#include "button.h"

int main(void)
{
    SDL_Window *win = NULL;
    SDL_Renderer *ren = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return -1;
    }

    win = SDL_CreateWindow("Button",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,0);
    if (!win)
    {
        SDL_Quit();
        return -1;
    }

    ren = SDL_CreateRenderer(win, -1, 0);
    if (!ren)
    {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return -1;
    }

    SDL_Rect btn;
    btn.w = 200;
    btn.h = 80;
    btn.x = (WINDOW_WIDTH - btn.w) / 2;
    btn.y = (WINDOW_HEIGHT - btn.h) / 2;

    int hovered = 0;
    int run = 1;
    SDL_Event event;

    while (run)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                run = 0;
            }

            handle_button(&btn, &event, &hovered);
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        if (hovered)
        {
            SDL_SetRenderDrawColor(ren, 80, 80, 80, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(ren, 180, 180, 180, 255);
        }

        SDL_RenderFillRect(ren, &btn);

        SDL_RenderPresent(ren);

        SDL_Delay(1000 / 24);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}