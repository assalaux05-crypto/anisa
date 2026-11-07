#ifndef ENEMY_H
#define ENEMY_H

#include "game_state.h"

#define ENEMY_DELAY_MS 2500

int enemy_wait(struct game *game);
void *enemy_worker(void *arg);

#endif // ENEMY_H
