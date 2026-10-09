#include "images.h"
#include <err.h>
#include <SDL2/SDL.h>
Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
  if (surface->format->BytesPerPixel != 4)
    {
        errx(1, "BytesPerPixel must be 4");
    }
    //octet par octet  unit8=1octet
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;

    return *(Uint32 *)p;
}

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    if (surface->format->BytesPerPixel != 4)
    {
        errx(1, "BytesPerPixel must be 4");
    }

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;

    *(Uint32 *)p = pixel;
}
