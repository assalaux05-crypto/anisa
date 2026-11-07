#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <pthread.h>
#include <stddef.h>

#include "airship.h"

#define LOG_SIZE 64
#define LOG_WIDTH 96
#define COMMAND_QUEUE 8
#define INPUT_SIZE 64

enum action
{
    SHOOT,
    REARM,
    REPAIR,
    BACKUP,
    HELP,
    QUIT,
    INVALID,
};

struct game
{
    struct airship *player;
    struct airship *enemy;
    int terminal;

    // protected by mutex
    int finished;
    char log[LOG_SIZE][LOG_WIDTH];
    size_t log_count;
    enum action commands[COMMAND_QUEUE];
    size_t command_count;
    char input[INPUT_SIZE];
    size_t input_len;

    pthread_mutex_t mutex;
    pthread_cond_t cond;

    // held during every action: shoot() locks the shooter then its target,
    // so two shots at the same time could deadlock
    pthread_mutex_t action_mutex;
};

int game_init(struct game *game);
void game_destroy(struct game *game);
void game_log(struct game *game, const char *message);
int game_is_finished(struct game *game);
void game_end(struct game *game);

#endif // GAME_STATE_H
