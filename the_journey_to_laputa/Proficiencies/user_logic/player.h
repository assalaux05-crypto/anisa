#ifndef PLAYER_H
#define PLAYER_H

#include "game_state.h"

void push_command(struct game *game, enum action action);
int next_command(struct game *game, enum action *action);
void *player_worker(void *arg);

#endif // PLAYER_H
