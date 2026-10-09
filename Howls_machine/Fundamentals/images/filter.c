#include "images.h"

void grayscale(SDL_Surface *surface)
{
   int w = surface->w;
    int h = surface->h;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            Uint32 pixel = get_pixel(surface, x, y);

            Uint8 r;
            Uint8 g;
            Uint8 b;
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);

            Uint8 gray = 0.299 * r + 0.587 * g + 0.114 * b;

            Uint32 newpixel = SDL_MapRGB(surface->format, gray, gray, gray);

            set_pixel(surface, x, y, newpixel);
        }
    }
}
