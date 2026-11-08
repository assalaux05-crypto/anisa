#include "input.h"

#include "../game_logic/actions.h"







//    enum action commands[COMMAND_QUEUE];


void push_command(struct game *game, enum action action)
{
    if (!game)
        return;

    int plein = 0;

    pthread_mutex_lock(&game->mutex);

    // 
    if (game->command_count == COMMAND_QUEUE)
    {
        plein = 1;
    }
    else
    {
        // add a la fin 
        game->commands[game->command_count] = action;
        game->command_count++;

        // wakes up 
        pthread_cond_broadcast(&game->cond);
    }

    pthread_mutex_unlock(&game->mutex);

   
    if (plein)
    {
        game_log(game, "The crew is overwhelmed, order ignored.");
    }
}




int next_command(struct game *game, enum action *action)
{
    if (!game || !action)
        return 0;

    pthread_mutex_lock(&game->mutex);

    // wait joueur pas fini et queue vide
    while (!game->finished && game->command_count == 0)
    {
        pthread_cond_wait(&game->cond, &game->mutex);
    }

    
    if (game->finished)
    {
        pthread_mutex_unlock(&game->mutex);
        return 0;
    }

    *action = game->commands[0];

    for (size_t i = 1; i < game->command_count; i++)
    {
        game->commands[i - 1] = game->commands[i];
    }

    game->command_count--;

    pthread_mutex_unlock(&game->mutex);

    return 1;
}



void *player_worker(void *arg)
{
    struct game *game = (struct game *)arg;

    if (!game)
        return NULL;

    enum action action;


    while (next_command(game, &action) == 1)
    {
        if (action == QUIT)
        {
            game_end(game);
            break; 
        }

       
        pthread_mutex_lock(&game->action_mutex);

        // Si la partie est toujours en cours
        if (game_is_finished(game) == 0)
        {
            apply_action(game, game->player, game->enemy, "Tiger Moth", action);
            check_end(game);
        }

        pthread_mutex_unlock(&game->action_mutex);
    }

    return NULL;
}