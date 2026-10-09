#include "images.h"
#include <err.h>
#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    SDL_Surface *surface = load_image(argv[1]);

    grayscale(surface);

    if (SDL_SaveBMP(surface, "grayscale.bmp") != 0)
    {
        SDL_FreeSurface(surface);
        errx(1, "%s", SDL_GetError());
    }

    printf("Image saved as grayscale.bmp\n");

    SDL_FreeSurface(surface);

    return 0;
}