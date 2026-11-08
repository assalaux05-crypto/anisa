#ifndef EXERCISE_H
#define EXERCISE_H
#include <stddef.h>
/* Read key from [server]. Return 0 if found, -1 otherwise. */
int ini_get(const char *filename, const char *section, const char *key,
            char *out, size_t out_size);
/* Add or replace key=value in a section. Return 0 or -1. */
int ini_set(const char *filename, const char *section, const char *key,
            const char *value);
/* Remove key from a section. Return 0 or -1. */
int ini_delete(const char *filename, const char *section, const char *key);
#endif
