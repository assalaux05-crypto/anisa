#include "include/airship.h"
#include "include/engine.h"
#include "include/update_crew.h"
#include "include/supplies.h"

#include <stdio.h>















int main(void)
{

    /*
    struct airship *init_airship(size_t capacity, int fuel, int ammunition,
                             int health, size_t nb_cannons) { 

    */
    struct airship* ship=init_airship(5,40,10,100,4);
    /*
    int update_crew(struct airship *ship, const char **names, size_t n) { 

    */
    const char *names[3];
    names[0]="Pazu";
    names[1]="Louis";
    names[2]="Dora";

    int res_up=update_crew(ship,names,3);
    if(res_up==42)
    {
        destroy_airship(ship);
        return 42;
    }

    //int load_supplies(struct airship *ship, int n, int amount) { 
    int res_supp=load_supplies(ship,3,20);
    if(res_supp==42)
    {
        destroy_airship(ship);
        return 42;
    }

    //int init_engines(struct airship *ship, const int *requirements, size_t n) { 
    int r[4];
    r[0]=10;
    r[1]=20;
    r[2]=30;
    r[3]=40;


    int res_eng=init_engines(ship,r,4);
    //int start_engines(struct airship *ship) { 
    if(res_eng==42)
    {
        destroy_airship(ship);
        return 42;
    }
                

    int res_s=start_engines(ship);
    if(res_s==42)
    {
        destroy_airship(ship);
        return 42;
    
    }
    size_t cpt=0;
    printf("Crew: %zu/%zu\n",ship->crew->crew_count,ship->crew->crew_capacity);
    for(size_t i=0;i<ship->nb_engine;i++)
    {
        if(ship->engines[i].started==1)
        {
            cpt++;
        }
    }
    printf("Engines started: %zu/%zu\n",cpt,ship->nb_engine);
    printf("Remaining fuel: %d\n",ship->fuel);
    destroy_airship(ship);
    return 0;

}