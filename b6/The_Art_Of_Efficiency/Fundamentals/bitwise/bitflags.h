#ifndef BITFLAGS_H
#define BITFLAGS_H
/*
struct firefly
{
    int big;
    int bright;
    int long_legs;
    int slow_flight;
    int turned_on;
    int invincible;
};
*/
struct firefly
{
    unsigned int big : 1; // int 1 bit au lieu 4
    unsigned int bright : 1;
    unsigned int long_legs : 1;
    unsigned int slow_flight : 1;
    unsigned int turned_on : 1;
    unsigned int invincible : 1;
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

struct firefly *firefly_init(void);

char firefly_get(struct firefly *firefly, enum firefly_attrib attrib);
void firefly_set(struct firefly *firefly, enum firefly_attrib attrib,
                 int value);

#endif /* ! BITFLAGS_H */
