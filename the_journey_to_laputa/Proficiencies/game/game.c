#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "game.h"
#include "display.h"
#include "enemy.h"
#include "player.h"
#include "input.h"




struct threads
{
    pthread_t enemy;
    pthread_t player;
    pthread_t display;
};






static void join_threads(struct threads *threads)
{
    if (!threads)
        return;

    pthread_join(threads->display, NULL);
    pthread_join(threads->enemy, NULL);
    pthread_join(threads->player, NULL);
}



static int start_threads(struct game *game, struct threads *threads)
{
    if (!game || !threads)
        return 1;
    //affichage
   
    if (pthread_create(&threads->display, NULL, display_worker, game) != 0)
    {
        return 1;
    }

    // threads ennemy
    if (pthread_create(&threads->enemy, NULL, enemy_worker, game) != 0)
    {
        game_end(game);
        pthread_join(threads->display, NULL);
        return 1;
    }


    if (pthread_create(&threads->player, NULL, player_worker, game) != 0)
    {
        game_end(game);
        pthread_join(threads->display, NULL);
        pthread_join(threads->enemy, NULL);
        return 1;
    }

    return 0;
}





int play_game(void)
{
    struct game game;
    struct threads threads;

    srand((unsigned int)time(NULL));
    if (game_init(&game) != 0)
    {
        return 1;
    }

    start_screen(&game);

    if (start_threads(&game, &threads) != 0)
    {
        stop_screen(&game);
        game_destroy(&game);
        return 1;
    }

    while (!game_is_finished(&game) && read_keys(&game) == 0)
    {
        // ca execute read_keys
    }

    join_threads(&threads);

    int res = print_result(&game);
    fflush(stdout);

    game_destroy(&game);

    return res;

}