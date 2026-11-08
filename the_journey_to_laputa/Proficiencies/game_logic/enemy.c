#include "actions.h"
#include "enemy.h"
#include <errno.h>
















static struct timespec deadline_in(int ms)
{
    struct timespec ts;

    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += ms / 1000;
    ts.tv_nsec += (long)(ms % 1000) * 1000000L;

    if (ts.tv_nsec >= 1000000000L)
    {
        ts.tv_sec++;
        ts.tv_nsec -= 1000000000L;
    }

    return ts;
}





int enemy_wait(struct game *game)
{
    if (!game)
        return 0;

    struct timespec deadline = deadline_in(ENEMY_DELAY_MS);
    int res = 0;

    pthread_mutex_lock(&game->mutex);

    while (game->finished != 1 && res != ETIMEDOUT)
    {
        res = pthread_cond_timedwait(&game->cond, &game->mutex, &deadline);
    }

    int agir_enemi;

    // temp limite termine 
    if (res == ETIMEDOUT && game->finished == 0)
    {
        agir_enemi = 1; 
    }
    else
    {
        agir_enemi = 0; // jeux end enemi agi pas 
    }
    pthread_mutex_unlock(&game->mutex);

    return agir_enemi;
}




void *enemy_worker(void *arg)
{
    struct game *game = (struct game *)arg;

    if (!game)
        return NULL;

    // le délai de 2,5  s'écoule et jeux pas fini
    while (enemy_wait(game) == 1)
    {
        pthread_mutex_lock(&game->action_mutex);

        if (game_is_finished(game) == 0)
        {
            
            enum action act = choose_enemy_action(game);

            apply_action(game, game->enemy, game->player, "Goliath", act);

            check_end(game);
        }
        pthread_mutex_unlock(&game->action_mutex);
    }

    return NULL;
}