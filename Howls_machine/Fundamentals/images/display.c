#include "images.h"
#include <err.h>
#include <stdio.h>


SDL_Texture *load_texture(SDL_Renderer *renderer, const char *path)
{
    SDL_Surface *s = load_image(path);

    printf("Image width: %dpx\n", s->w);
    printf("Image height: %dpx\n", s->h);
    printf("Bytes per pixel: %d\n", s->format->BytesPerPixel);

    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
    if (t == NULL)
    {
        SDL_FreeSurface(s);
        errx(1, "%s", SDL_GetError());
    }

    SDL_FreeSurface(s);

    return t;
}





int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        errx(1, "%s", SDL_GetError());
    }

    int win_w= 800;
    int win_h= 600;

    SDL_Window *w = SDL_CreateWindow("Display",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,win_w,win_h,SDL_WINDOW_SHOWN);
    if (w == NULL)
    {
        SDL_Quit();
        errx(1, "%s", SDL_GetError());
    }

    SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
    if (r == NULL)
    {
        SDL_DestroyWindow(w);
        SDL_Quit();
        errx(1, "%s", SDL_GetError());
    }

    SDL_Texture *t = load_texture(r, argv[1]);

    int img_w = 0;
    int img_h = 0;
    SDL_QueryTexture(t, NULL, NULL, &img_w, &img_h);

    SDL_Rect dst;
    dst.w = img_w;
    dst.h = img_h;
    dst.x = (win_w- img_w) / 2;
    dst.y = (win_h- img_h) / 2;

    int running = 1;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);
        SDL_RenderCopy(r, t, NULL, &dst);
        SDL_RenderPresent(r);
    }

    SDL_DestroyTexture(t);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();

    return 0;
}