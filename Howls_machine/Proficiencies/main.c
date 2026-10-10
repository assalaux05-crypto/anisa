#include "tic_tac_toe.h"
#include <stdio.h>

int main(void)
{
 

    /*
     * TODO: Initialize the window
     */
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    init_window(&window, &renderer);
    int board[3][3] = { 0 };
    int player = 1;

    int running = 1;
    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            
        if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = 0;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int cell = get_clicked_cell(event.button.x, event.button.y);
                    int row = cell / 3;
                    int col = cell % 3;

                    handle_click(board, row, col, &player);

                    int winner = check_winner(board);
                    if (winner != 0)
                    {
                        printf("Joueur %d a gagne!\n", winner);
                        running = 0;
                    }
                    else if (is_board_full(board))
                    {
                        printf("egalité\n");
                        running = 0;
                    }
                }
            }
        }

        /*
         * TODO:
         * - Clear the previous frame
         * - Draw the board.
         * - Draw the players' marks.
         * - Render the new frame
         */
       
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_board(renderer);
        draw_marks(renderer, board);
        SDL_RenderPresent(renderer);
    }

    terminate(window, renderer);

    return 0;
}
