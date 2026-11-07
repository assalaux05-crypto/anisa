#include "../include/airship.h"
#include "../include/engine.h"

#include <stdlib.h>

/*


struct crew
{
    char **members;
    size_t crew_count;
    size_t crew_capacity;
};

struct airship
{
    // crew
    struct crew *crew;

    // ressource
    int fuel;
    int ammunition;

    // health
    int health;
    int max_health;

    // Cannons
    size_t nb_cannons;
    sem_t cannon_slots;

    // synchronisation
    pthread_mutex_t mutex;
    pthread_cond_t engine_cond;

    // Engines
    struct engine *engines;
    size_t nb_engine;
};


*/
struct airship *init_airship(size_t capacity, int fuel, int ammunition,
                             int health, size_t nb_cannons) { 


        //capacity type size_t peux etre negative
        if (capacity==0 || health<=0)return NULL;
        if(fuel<0 || ammunition<0)return NULL;
        if(nb_cannons<1 || nb_cannons>4)return NULL;

        struct airship* ship=malloc(sizeof(struct airship));
        if (!ship)return NULL;
        ship->crew=malloc(sizeof(struct crew));
        if(!ship->crew)
        {
            free(ship);
            return NULL;

        }
        //ship->crew->members=calloc(capacity*sizeof(char*)); remplis directement avec NULL

        ship->crew->members=malloc(capacity*sizeof(char*));
        if(!ship->crew->members)
        {
            free(ship->crew);
            free(ship);
            
            return NULL;
        }

        for(size_t i=0; i<capacity;i++)
        {
            ship->crew->members[i]=NULL;
        }
        ship->crew->crew_count=0;
        ship->crew->crew_capacity=capacity;
        ship->fuel = fuel;
        ship->ammunition=ammunition;
        ship->health=health;
        ship->max_health=health;
        ship->nb_cannons=nb_cannons;
        ship->engines=NULL;
        ship->nb_engine=0;
        // faut tjr utiliser une fct pour remplir pas affectation directe
        if(sem_init(&ship->cannon_slots,0,nb_cannons)!=0)
        {

            free(ship->crew->members);
            free(ship->crew);

            free(ship);

            return NULL;
        }
        if(pthread_mutex_init(&ship->mutex,NULL)!=0)
        {
            sem_destroy(&ship->cannon_slots);
            free(ship->crew->members);
            free(ship->crew);

            free(ship);
            return NULL;
        }
        if(pthread_cond_init(&ship->engine_cond,NULL)!=0)
        {
            pthread_mutex_destroy(&ship->mutex);
            sem_destroy(&ship->cannon_slots);
            
            free(ship->crew->members);
            free(ship->crew);
            free(ship);
            return NULL;
        }
        

        return ship;



                             }



void destroy_airship(struct airship *ship) { 
    if(!ship)return ;
    sem_destroy(&ship->cannon_slots);
    pthread_mutex_destroy(&ship->mutex);
    pthread_cond_destroy(&ship->engine_cond);
    destroy_engines(ship);
    if(ship->crew)
    {
        if(ship->crew->members)
        {
            for(size_t i=0;i<ship->crew->crew_capacity;i++)
            {
                free(ship->crew->members[i]);
            }
            free(ship->crew->members);
        }
        free(ship->crew);

    }
free(ship);
 
   
    



}
