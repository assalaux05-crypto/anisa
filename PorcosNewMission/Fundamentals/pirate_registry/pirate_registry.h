#ifndef PIRATE_REGISTRY_H
#define PIRATE_REGISTRY_H
#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Pirate
{
    char name[64];
    char plane[64];
    int danger_level;
};

int write_pirates_file(const char *filename, const struct Pirate *pirates,
                       size_t n);
int read_pirates_file(const char *filename, struct Pirate *pirates, size_t n);
int parse_line(char *line, struct Pirate *p);

#endif // !PIRATE_REGISTRY_H
