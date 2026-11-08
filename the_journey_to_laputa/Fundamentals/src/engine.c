
#include "../include/engine.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*

struct engine_args
{
    struct airship *ship;
    struct engine *engine;
    size_t *working;
};
struct engine
{
    int required_fuel;
    int started;
};

*/



int init_engines(struct airship *ship,
                 const int *requirements, size_t n) { 

        

    if(!ship || !requirements || n==0 ||ship->engines!=NULL || ship->nb_engine != 0)return 42;
    for(size_t i=0;i<n;i++)
    {
        if(requirements[i]<=0)return 42;

    }
    ship->engines=malloc(sizeof(struct engine)*n);
    if(!ship->engines)return 42;
    for(size_t i=0;i<n;i++)
    {
        
        ship->engines[i].required_fuel=requirements[i];
        ship->engines[i].started=0;
    }
    ship->nb_engine=n;
    return 0;


                 }

// fct pour chaque t
// qd jai cond il faut une bouvle et le lock et unlock
void* start_engine(void*arg) //just move fct_t to start_engine
{


    struct engine_args*box=(struct engine_args*)arg;
    pthread_mutex_lock(&box->ship->mutex);
    while((*box->working)>=2)
    {
    pthread_cond_wait(&box->ship->engine_cond,&box->ship->mutex);
    }
    (*box->working)++;
    box->ship->fuel-=box->engine->required_fuel;
    pthread_mutex_unlock(&box->ship->mutex);// t1 unlock est va dormir 

    sleep(1);
    
    pthread_mutex_lock(&box->ship->mutex);//t1 loc ps box->working var partage donc il faut qui lock
    box->engine->started=1;
    (*box->working)--;
    pthread_cond_signal(&box->ship->engine_cond);
    pthread_mutex_unlock(&box->ship->mutex);//unlock a la fin pou que le t2 peux travaille

    return NULL;
}
// je pense tjr a boxes pour regrouper tous les workers pour faciliter la tache et joublie pas de la free en cas derreur 
// je remplis chaque bos de boes dans le for et je fais ettention au type 
int start_engines(struct airship *ship) { 


    if(ship==NULL || ship->engines==NULL || ship->nb_engine==0)return 42;
    
    int s=0;
    pthread_mutex_lock(&ship->mutex);

    for(size_t i=0;i<ship->nb_engine;i++)
    {
        if (ship->engines[i].started != 0)
        {
            pthread_mutex_unlock(&ship->mutex);
            return 42;
        }
        
        s+=ship->engines[i].required_fuel;
    }

    if (ship->fuel < s)
    {
        pthread_mutex_unlock(&ship->mutex);
        return 42;
    }

    pthread_mutex_unlock(&ship->mutex);



    pthread_t *t=malloc(sizeof(pthread_t)*ship->nb_engine);
    if(!t)return 42;
    struct engine_args*boxes=malloc(sizeof(struct engine_args)*ship->nb_engine);
    if(!boxes)
    {
        free(t);
        return 42;
    }
    size_t s_count=0;
    //creation t
    for(size_t i=0;i<ship->nb_engine;i++)
    {
      
        boxes[i].ship=ship;
        boxes[i].engine=&ship->engines[i];// faut pas que joublie & 
        boxes[i].working=&s_count;//ptr a voir
        if(pthread_create(&t[i],0,start_engine,&boxes[i])!=0)
        {
            for(size_t j=0;j<i;j++)
            {
                pthread_join(t[j],NULL);
            }
            free(boxes);
            free(t);
            return 42;
        }
        
    }
    // attendre t
    int res=0;
    for(size_t j=0;j<ship->nb_engine;j++)
        {
           if( pthread_join(t[j],NULL)!=0)
           {
            res=42;
           }

        }






   free(t);
   free(boxes);
   return res;



}


/*
struct engine
{
    int required_fuel;
    int started;
};

*/
/*
    for(size_t i=0;i<ship->nb_engine;i++)


*/

void destroy_engines(struct airship *ship) { 


    if(!ship || !ship->engines)return ;


    free(ship->engines);
    ship->engines=NULL;
    ship->nb_engine=0;







}