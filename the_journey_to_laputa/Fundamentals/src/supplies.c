
#include "../include/supplies.h"

#include <stdlib.h>

void *load_worker(void *arg) { 

struct load_args* box=(struct load_args* )arg;

    pthread_mutex_lock(&box->ship->mutex);
    box->ship->fuel+=box->amount;
    pthread_mutex_unlock(&box->ship->mutex);
return NULL;


}


/*
struct load_args
{
    struct airship *ship;
    int amount;
};

*/



int load_supplies(struct airship *ship, int n, int amount) { 


    if (ship==NULL || n<0 || amount <0)return 42;
    if(n==0 || amount==0)return 0;
   // pthread_t t[n];
   pthread_t* t=malloc(sizeof(pthread_t)*n);
   if(!t)return 42;
    struct load_args* arg=malloc(sizeof(struct load_args));
    if(!arg)return 42;
    
    arg->ship=ship;
    arg->amount=amount;
    for (int i=0;i<n;i++)
    {
        if(pthread_create(&t[i],0,load_worker,arg)!=0)
        {
             for(int j=0;j<i;j++)

            {
                pthread_join(t[j],NULL);
                
            }
            free(arg);
            return 42;
        }
    }
    for(int i=0;i<n;i++)
    {
       if(pthread_join(t[i],NULL)!=0)
       {
        free(t);
        free(arg);
        return 42;
       }
    }
    free(t);
    free(arg);
    return 0;

}
/*

int main(void)
{
    struct airship *ship = init_airship(5, 100, 10, 100, 4);
    if (ship == NULL)
        return 42;

    printf("Initial fuel: %d\n", ship->fuel);

    if (load_supplies(ship, 5, 1000) != 0)
    {
        destroy_airship(ship);
        return 42;
    }

    printf("Final fuel: %d\n", ship->fuel);

    destroy_airship(ship);
    return 0;
}
*/