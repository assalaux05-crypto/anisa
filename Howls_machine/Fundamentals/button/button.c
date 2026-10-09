#include "button.h"

int is_inside(SDL_Rect *button, int x, int y)
{
   

    if (x >= button->x && x < button->x + button->w &&
        y >= button->y && y < button->y + button->h)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    }

void handle_button(SDL_Rect *button, SDL_Event *event, int *hovered)
{
    

    int x = 0;
    int y = 0;

    if (event->type == SDL_MOUSEMOTION)
    {
        x = event->motion.x;
        y = event->motion.y;

        if (is_inside(button, x, y))
        {
            *hovered = 1;
        }
        else
        {
            *hovered = 0;
        }
    }

    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            x = event->button.x;
            y = event->button.y;

            if (is_inside(button, x, y))
            {
                printf("Button clicked!\n");
            }
        }
    }
}
