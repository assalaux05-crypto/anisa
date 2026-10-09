#include "window.h"
#include <SDL2/SDL.h>
void init_window(SDL_Window **window, SDL_Renderer **renderer)
{
    (void)window;
    (void)renderer;

    // TODO
    int res=SDL_Init(SDL_INIT_VIDEO);
    if (res!=0)return ;
    *window=SDL_CreateWindow("Projection",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if(!(*window))
    {
        SDL_Quit();
        return ;
    }
    *renderer=SDL_CreateRenderer(*window,-1,SDL_RENDERER_SOFTWARE  |SDL_RENDERER_PRESENTVSYNC  );
    if(!(*renderer))
    {
        SDL_DestroyWindow(*window);
        *window=NULL;
        SDL_Quit();

        return ;
    }
}   

void terminate(SDL_Window *window, SDL_Renderer *renderer)
{
    (void)window;
    (void)renderer;

    // TODO
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();




}
/*
int main(void)
{


SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    init_window(&window, &renderer);
    printf("Window created!\n");
    SDL_Delay(4000); // Gives you time to see the window
    terminate(window, renderer);

    printf("Window terminated!\n");
    return EXIT_SUCCESS;



}
*/
