
#include <stdio.h>
#include "game_state.h"
#include <pthread.h>
#include "../game_logic/actions.h"

/*

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



*/


// iniy ou pas les enum
static int init_sync(struct game *game)
{
    if (!game)
        return 1;

    if (pthread_mutex_init(&game->mutex, NULL) != 0)
    {
        return 1;
    }

    if (pthread_mutex_init(&game->action_mutex, NULL) != 0)
    {
        pthread_mutex_destroy(&game->mutex);
        return 1;
    }

    if (pthread_cond_init(&game->cond, NULL) != 0)
    {
        pthread_mutex_destroy(&game->action_mutex);
        pthread_mutex_destroy(&game->mutex);
        return 1;
    }

    return 0;
}
int game_init(struct game *game) { 


    if (!game)
    {
        return 1;
    }
    game->player = new_ship(12, 100, "tiger-moth");
    if (!game->player)
    {
        return 1;
    }

    game->enemy = new_ship(16, 150, "goliath");
    if (!game->enemy)
    {
        destroy_airship(game->player);
        return 1;
    }

   
    game->terminal = 0;
    game->finished = 0;
    game->log_count = 0;
    game->command_count = 0;
    game->input_len = 0;
    game->input[0] = '\0';
    // init  la ou c mutex et cond 
    if (init_sync(game) != 0)
    {
        destroy_airship(game->enemy);
        destroy_airship(game->player);
        return 1;
    }

    return 0;




}



void game_destroy(struct game *game)
{
    if (!game)
    {
        return;
    }

    pthread_cond_destroy(&game->cond);
    pthread_mutex_destroy(&game->action_mutex);
    pthread_mutex_destroy(&game->mutex);

    destroy_airship(game->player);
    destroy_airship(game->enemy);
}



void game_log(struct game *game, const char *message) { 
    if(!game || !message)return ;
    pthread_mutex_lock(&game->mutex);

    // log width =nb clone 
    //log size =nb ligne
    snprintf(game->log[game->log_count%LOG_SIZE],LOG_WIDTH,"%s",message);
    game->log_count++;

    pthread_mutex_unlock(&game->mutex);







}



int game_is_finished(struct game *game)
{
    if (!game)
    {
        return 1;
    }

    pthread_mutex_lock(&game->mutex);
    int res = game->finished;
    pthread_mutex_unlock(&game->mutex);

    return res;
}