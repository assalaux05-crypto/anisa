#ifndef FLIGHT_LOG_H
#define FLIGHT_LOG_H

#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Mission
{
    char *date;
    char *mission_type;
    double bounty;
};

struct Mission *alloc_missions(size_t n);
void init_mission(struct Mission *missions, size_t i, char *date, char *type,
                  double bounty);
void free_missions(struct Mission *missions, size_t n);
double total_bounty(struct Mission *missions, size_t n);
struct Mission *max_bounty(struct Mission *missions, size_t n);

#endif // !FLIGHT_LOG_H
