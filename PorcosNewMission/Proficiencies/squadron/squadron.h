#ifndef SQUADRON_HEADER
#define SQUADRON_HEADER

#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct seaplane
{
    size_t tail_number;
    struct seaplane *front;
    struct seaplane *back;
};

struct squadron
{
    struct seaplane *head;
    struct seaplane *tail;
    size_t size;
};

enum flypast
{
    FRONT_FIRST,
    BACK_FIRST,
};

struct seaplane *create_seaplane(size_t tail_number);
struct squadron *create_squadron();
void free_squadron(struct squadron *s);

void squadron_prepend(struct squadron *s, struct seaplane *p);
void squadron_append(struct squadron *s, struct seaplane *p);
void squadron_remove(struct squadron *s, size_t index);
void print_squadron(struct squadron *s, enum flypast m);

#endif // SQUADRON_HEADER
