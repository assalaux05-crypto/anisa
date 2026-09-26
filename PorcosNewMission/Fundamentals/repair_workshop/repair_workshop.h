#ifndef REPAIR_WORKSHOP_H
#define REPAIR_WORKSHOP_H

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Repair
{
    char client[32];
    char repair_type[64];
    char date[16];
    double cost;
    struct Repair *next;
};

void add_repair(struct Repair **head, struct Repair *r);
struct Repair *load_repairs(const char *filename);
int save_repairs(const char *filename, const struct Repair *head);
struct Repair *sort_repairs(struct Repair *head,
                            int (*compare_fn)(const struct Repair *,
                                              const struct Repair *));

void free_repairs(struct Repair *head); // Auxilary function

#endif // !REPAIR_WORKSHOP_H
