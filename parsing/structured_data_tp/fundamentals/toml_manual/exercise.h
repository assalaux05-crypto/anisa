#ifndef EXERCISE_H
#define EXERCISE_H
#include <stddef.h>
/* Read key from a TOML table. Return 0 or -1. */
int toml_get(const char *filename, const char *table, const char *key,
             char *out, size_t out_size);
/* Replace an existing integer value. Return 0 or -1. */
int toml_update_int(const char *filename, const char *table,
                    const char *key, int value);
#endif
