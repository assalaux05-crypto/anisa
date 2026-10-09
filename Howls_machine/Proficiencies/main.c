#include "tic_tac_toe.h"

int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    /*
     * TODO: Initialize the window
     */

    int board[3][3] = { 0 };
    int player = 1;

    int running = 1;
    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            /*
             * TODO:
             * Set running to 0 if an SDL_QUIT event is received or if the
             * Escape key is pressed
             *
             * If a left click happened:
             *   - Find the clicked cell.
             *   - Play the corresponding move.
             *   - Check if one of the players won.
             *   - Check if the board is full.
             *   - Print the result and stop the game when it ends.
             */
        }

        /*
         * TODO:
         * - Clear the previous frame
         * - Draw the board.
         * - Draw the players' marks.
         * - Render the new frame
         */
    }

    terminate(window, renderer);

    return 0;
}
