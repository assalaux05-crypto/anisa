#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <SDL2/SDL.h>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 600

// render.c
void init_window(SDL_Window **window, SDL_Renderer **renderer);
void terminate(SDL_Window *window, SDL_Renderer *renderer);
void draw_board(SDL_Renderer *renderer);
void draw_cross(SDL_Renderer *renderer, int row, int col);
void draw_square(SDL_Renderer *renderer, int row, int col);
void draw_marks(SDL_Renderer *renderer, int board[3][3]);

// game.c
int get_clicked_cell(int x, int y);
void handle_click(int board[3][3], int row, int col, int *player);
int is_board_full(int board[3][3]);
int check_winner(int board[3][3]);

#endif /* ! TIC_TAC_TOE_H */
