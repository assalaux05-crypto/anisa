#include "bitflags.h"
#include <stddef.h>
#include <stdlib.h>
/*

struct firefly
{
    unsigned int big: 1;
    int bright;
    int long_legs;
    int slow_flight;
    int turned_on;
    int invincible;
};

enum firefly_attrib
{
    FLAG_BIG = 0,
    FLAG_BRIGHT = 1,
    FLAG_LONG_LEGS = 2,
    FLAG_SLOW_FLIGHT = 3,
    FLAG_TURNED_ON = 4,
    FLAG_INVINCIBLE = 5,
};










*/
struct firefly *firefly_init(void)
{
    struct firefly*box=malloc(sizeof(struct firefly));
    if(!box)return NULL;
    box->big = 0;
    box->bright = 0;
    box->long_legs = 0;
    box->slow_flight = 0;
    box->turned_on = 0;
    box->invincible = 0;

    return box;
}

char firefly_get(struct firefly *firefly, enum firefly_attrib attrib)
{
    
    
   if (attrib == FLAG_BIG)
   {
    return firefly->big;
   }
        
    else if (attrib == FLAG_BRIGHT)
    {
                return firefly->bright;

    }
    else if (attrib == FLAG_LONG_LEGS)
    {
                return firefly->long_legs;

    }
    else if (attrib == FLAG_SLOW_FLIGHT)
    {
        return firefly->slow_flight;

    }
    else if (attrib == FLAG_TURNED_ON)
    {
        return firefly->turned_on;

    }
    else if (attrib == FLAG_INVINCIBLE)
    {
        return firefly->invincible;

    }
    else
    {
                return 0;

    }




}

void firefly_set(struct firefly *firefly, enum firefly_attrib attrib, int value)
{
    
   


    if (attrib == FLAG_BIG)
   {
     firefly->big=value;
   }
        
    else if (attrib == FLAG_BRIGHT)
    {
         firefly->bright =value ;

    }
    else if (attrib == FLAG_LONG_LEGS)
    {
        firefly->long_legs =value ;

    }
    else if (attrib == FLAG_SLOW_FLIGHT)
    {
        firefly->slow_flight =value ;

    }
    else if (attrib == FLAG_TURNED_ON)
    {
        firefly->turned_on =value ;

    }
    else if (attrib == FLAG_INVINCIBLE)
    {
         firefly->invincible =value ;

    }
   

}


/*
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct firefly *firefly = firefly_init();

    firefly_set(firefly, FLAG_LONG_LEGS, 1);
    firefly_set(firefly, FLAG_INVINCIBLE, 1);

    printf("big: %d\n", firefly_get(firefly, FLAG_BIG));
    printf("long legs: %d\n", firefly_get(firefly, FLAG_LONG_LEGS));
    printf("slow_flight: %d\n", firefly_get(firefly, FLAG_SLOW_FLIGHT));
    printf("invicible: %d\n", firefly_get(firefly, FLAG_INVINCIBLE));

    free(firefly);

    return 0;

}
*/