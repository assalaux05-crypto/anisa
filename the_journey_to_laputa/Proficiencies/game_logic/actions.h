#ifndef ACTIONS_H
#define ACTIONS_H

#include "game_state.h"

// a new airship (4 crew places, 4 cannons) with 2 pirates "<prefix>-1",
// "<prefix>-2"; NULL on error
struct airship *new_ship(int ammunition, int health, const char *prefix);

// Given: the rules of the game. Call them with game->action_mutex held.

void do_shoot(struct game *game, struct airship *self, struct airship *target,
              const char *name);
void do_rearm(struct game *game, struct airship *self, const char *name);
void do_repair(struct game *game, struct airship *self, const char *name);
void do_backup(struct game *game, struct airship *self, const char *name);

// self does the action against target, name is used in the messages
void apply_action(struct game *game, struct airship *self,
                  struct airship *target, const char *name, enum action action);
// the next action of the enemy
enum action choose_enemy_action(struct game *game);
// ends the game (game_end) once a ship is shot down
void check_end(struct game *game);

#endif // ACTIONS_H
