#ifndef INPUT_H
#define INPUT_H

#include "game_state.h"

// Given: everything that reads the keyboard.

// action of a command ("shoot", "rearm"...), INVALID if unknown
enum action parse_input(const char *line);
// a line was typed: answers help and mistakes, gives the actions to the
// player's thread with push_command
void submit_line(struct game *game, const char *line);
// adds a key to game->input, enter submits the line
void handle_key(struct game *game, char key);
// waits at most 50 ms for keys and handles them; returns 1 once stdin is
// closed, 0 otherwise
int read_keys(struct game *game);

#endif // INPUT_H
