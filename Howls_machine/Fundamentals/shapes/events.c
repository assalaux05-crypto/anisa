#include "shapes.h"
#include <SDL2/SDL.h>
int handle_events(SDL_Rect *rectangle)
#define step 200
{
    (void)rectangle;
     SDL_Event event;
     /*
        
    typedef struct SDL_Rect {
  9     int x, y;
 10     int w, h;
     */
     while(SDL_PollEvent(&event))
    {
        if (event.type==SDL_QUIT)return 0;
       // if (event.type==Escape)return 0;
        if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym ==SDLK_SPACE)return 0;
            else if (event.key.keysym.sym==SDLK_UP)
            {
                rectangle->y-= step;    
            }
            else if (event.key.keysym.sym==SDLK_DOWN)
            {
                rectangle->y+=step;
            }
            else if (event.key.keysym.sym== SDLK_LEFT)
            {
                rectangle->x-=step;
            }
            else if (event.key.keysym.sym==SDLK_RIGHT)
            {
                rectangle->x+= step;
                
            }                        
        }
        
        if (rectangle->x >0 )
        {
            rectangle->x=0;
        }
        if (rectangle->y<0)
        {
            rectangle->y=0;
        }
        if (rectangle->x + rectangle->w > WINDOW_WIDTH)
        {
            rectangle->x= WINDOW_WIDTH - rectangle->w;
        }
        if (rectangle ->y + rectangle->h <0)
        {
            rectangle ->y= WINDOW_HEIGHT - rectangle->h;
        }

        
    }
    return 1;
}
