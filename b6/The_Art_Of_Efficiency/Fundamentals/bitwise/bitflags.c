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
    struct firefly *box = malloc(sizeof(struct firefly));
    if (!box) return NULL;
    box->flags = 0;
    return box;
}

char firefly_get(struct firefly *firefly,
                 enum firefly_attrib attrib)
{
    int wght = 1;
    for (int i = 0; i < attrib; i++)
        wght *= 2;
    return (firefly->flags / wght) % 2;
}

void firefly_set(struct firefly *firefly,
                 enum firefly_attrib attrib,
                 int value)
{
    int wght = 1;
    for (int i = 0; i < attrib; i++)
        wght *= 2;
    if (value != 0)
    {
        if ((firefly->flags / wght) % 2 == 0)
            firefly->flags += wght;
    }
    else
    {
        if ((firefly->flags / wght) % 2 == 1)
            firefly->flags -= wght;
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