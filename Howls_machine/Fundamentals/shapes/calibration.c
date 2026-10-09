#include "shapes.h"
#include <SDL2/SDL.h>
void draw_calibration(SDL_Renderer *renderer)
{
    (void)renderer;

    /*
    typedef struct SDL_Rect {
    int x, y;
    int w, h;
} SDL_Rect;
    */
    // TODO
    int res=SDL_SetRenderDrawColor(renderer,30,30,30,255);
    if(res!=0)return ;
    int ress= SDL_RenderClear(renderer);
    if(ress!=0)return ;
    /*
    Projection area:

    Position: (100, 100)
    Size: 600x400

    */
    SDL_Rect pa;
    pa.x=100;
    pa.y=100;
    pa.w=600;
    pa.h=400;
    int colorpa=SDL_SetRenderDrawColor(renderer,255,255,255,255);
    if(colorpa!=0)return ;
    int r=SDL_RenderDrawRect(renderer,&pa);
    if(r!=0)return ;
    /*
    Reference block:

    Position: (350, 250)
    Size: 100x100

    */
    SDL_Rect rb;
    rb.x=350;
    rb.y=250;
    rb.w=100;
    rb.h=100;
    int colorrb=SDL_SetRenderDrawColor(renderer,255,0,0,255);
    if(colorrb!=0)return;
    int resrb=SDL_RenderFillRect(renderer,&rb);
    if(resrb!=0)return;
    /*
    Alignment line:

    From (100, 100)
    To (700, 500)

    */
    int coloral=SDL_SetRenderDrawColor(renderer,0,255,0,255);
    if(coloral!=0)return ;
    int resal=SDL_RenderDrawLine(renderer,100,100 , 700, 500);
    if(resal!=0)return;
    SDL_RenderPresent(renderer);
}   
