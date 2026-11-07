#ifndef DISPLAY_H
#define DISPLAY_H

#include <stddef.h>

#include "game_state.h"

// Given: everything that writes on the screen.

// color of a health bar, from the percentage value / max
const char *bar_color(int value, int max);
// health bar of 20 blocks
void print_bar(int value, int max);
// one line of stats: health, ammunition and crew of a ship
void print_ship(const char *name, struct airship *ship);
// the frame of stats of both ships
void print_stats(struct game *game);
// prints "> " and the line being typed, returns the number of characters
size_t print_prompt(struct game *game);
// prints the last count messages of the log
void print_log(struct game *game, size_t count);
// redraws the whole screen: stats, prompt and last messages
void draw_screen(struct game *game, int final);
// output not a terminal: prints the messages not printed yet
void print_new_messages(struct game *game, size_t *printed);

// routine of the display thread: redraws the screen every 50 ms until the
// game is finished
void *display_worker(void *arg);

// before the threads start: raw mode, first drawing, first message
void start_screen(struct game *game);
// leaves raw mode (call it if the game stops before print_result)
void stop_screen(struct game *game);
// after the threads are joined: stop_screen, then prints the result;
// returns 0 on a victory, 1 otherwise
int print_result(struct game *game);

#endif // DISPLAY_H
