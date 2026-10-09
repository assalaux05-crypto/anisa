#include "images.h"
#include <err.h>
#include <SDL2/SDL.h>

SDL_Surface *load_image(const char *path)
{
    SDL_Surface *s = SDL_LoadBMP(path);

    if (s == NULL)
    {
        errx(1, "%s", SDL_GetError());
    }

    return s;
}

void save_image(SDL_Surface *image, const char *path)
{
  

    if (SDL_SaveBMP(image, path) != 0)
    {
        errx(1, "%s", SDL_GetError());
    }
}
