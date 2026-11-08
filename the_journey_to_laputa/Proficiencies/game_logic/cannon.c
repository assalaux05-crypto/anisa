

#include "cannon.h"
#include "stdlib.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/airship.h"

//struct airship *init_airship(size_t nb_cannons, int fuel, int ammunition, int health, size_t crew_capacity);
//void destroy_airship(struct airship *ship);
//int update_crew(struct airship *ship, const char **pirates, size_t count);
/*
struct cannon_args
{
    struct airship *ship;
    struct airship *enemy;
    int result;
};
*/
/*

struct engine
{
    int required_fuel;
    int started;
};

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


int cannon_hit(void) { 

    // entre 0 et 99
    int nb=rand()%100;
    if (nb <75)
    {
        return 1;
    }
    return 0;



}

int shoot(struct airship *ship, struct airship *enemy) { 

    if(!ship || !enemy || ship==enemy )return 42;
    if(pthread_mutex_lock(&ship->mutex)!=0)return 42;
    if(pthread_mutex_lock(&enemy->mutex)!=0)
    {
        pthread_mutex_unlock(&ship->mutex);
        return 42;
    }
    // tir impossi
    if(ship->ammunition<=0)
    {
       int a= pthread_mutex_unlock(&ship->mutex);
       int b= pthread_mutex_unlock(&enemy->mutex);
        if(a!=0 || b!=0)return 42;
        return -1;
    }
    if(enemy->health==0)
    {
       int a= pthread_mutex_unlock(&ship->mutex);
       int b= pthread_mutex_unlock(&enemy->mutex);
       if(a!=0 || b!=0)return 42;

        return -1;
    }
    ship->ammunition--;
    int res=cannon_hit();
    if(res==1)
    {
        enemy->health-=10;
        if (enemy->health<0)
        {
            enemy->health=0;
        }

    }
   
        int a= pthread_mutex_unlock(&ship->mutex);
        int b= pthread_mutex_unlock(&enemy->mutex);
        if(a!=0 || b!=0)return 42;
        
    return 0;



}
// fct de caque ouvrier
// sem_waait comm mutex mais il compte les place vide
void *fire_cannon(void *arg) { 


    struct cannon_args*box=(struct cannon_args*)arg;
    
    while(sem_wait(&box->ship->cannon_slots)==-1)
    {
        if(errno!=EINTR)
        {
            box->result=42;
            return NULL;
        }
    }
    int res=shoot(box->ship,box->enemy);
    if(res==0)// tir effectue 
    {
        sleep(1);
    }
    else if(res==42)
    {
        box->result=42;
    }
    if(sem_post(&box->ship->cannon_slots)==-1)        // liberer le anon 

    {
                    box->result=42;

    }
    return NULL;



}








/*
struct cannon_args
{
    struct airship *ship;
    struct airship *enemy;
    int result;
};


*/

//Each worker must receive its own struct cannon_args
int fire_cannons(struct airship *ship,struct airship *enemy,size_t nb_shots) { 


    if(!ship || !enemy || ship==enemy || !ship->crew || ship->nb_cannons<1 || ship->nb_cannons>4)return 42;

    if(nb_shots==0 || ship->crew->crew_count==0)return 0;

    // nb_thread =min(nb_shots, 4, ship->crew->crew_count)
    size_t cpt=nb_shots;
    if (cpt>4)
    {
        cpt=4;
    }
    if (cpt>ship->crew->crew_count)
    {
        cpt=ship->crew->crew_count;
    }
    pthread_t* t=malloc(sizeof(pthread_t )*cpt);
    if(!t)return 42;
    struct cannon_args*boxes=malloc(sizeof(struct cannon_args)*cpt);
    if(!boxes)
    {
        free(t);

        return 42;
    }
    
    for (size_t i=0;i<cpt;i++)
    {
        boxes[i].ship=ship;
        boxes[i].enemy=enemy;
        boxes[i].result=0;
        if(pthread_create(&t[i],0,fire_cannon,&boxes[i])!=0)
        {
            for (size_t j=0;j<i;j++)
            {
                pthread_join(t[j],NULL);
               
            }
            //si t4  je free apres avoir attendre tous le worker avant t4
            free(boxes);
            free(t);
            return 42;
        }

    }
    int r=0;
    for(size_t i=0;i<cpt;i++)
    {
        pthread_join(t[i],NULL);
        if(boxes[i].result==42)
                {
                    r=42;
                }

    }
    free(boxes);
    free(t);
    return r;















                 }

/*

int main(void)
{
    struct airship *ship = init_airship(4, 0, 10, 100, 4);
    struct airship *enemy = init_airship(1, 0, 0, 100, 4);

    if (ship == NULL || enemy == NULL)
    {
        destroy_airship(ship);
        destroy_airship(enemy);
        return 42;
    }

    const char *pirates[] = {
        "Pazu", "Louis", "Charles", "Dora"
    };

    int result = update_crew(ship, pirates, 4);

    if (result == 0)
        result = fire_cannons(ship, enemy, 4);

    if (result == 0)
    {
        printf("Remaining ammunition: %d\n",
               ship->ammunition);
        printf("Enemy health: %d\n", enemy->health);
    }

    destroy_airship(ship);
    destroy_airship(enemy);
    return result;
}
*/