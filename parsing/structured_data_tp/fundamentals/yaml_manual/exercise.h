#ifndef EXERCISE_H
#define EXERCISE_H
#include <stddef.h>
/* Read a scalar from the simple top-level key: value subset. */
int yaml_get(const char *filename, const char *key, char *out, size_t out_size);
/* Replace a top-level scalar or append it if absent. */
int yaml_set(const char *filename, const char *key, const char *value);
/* Count simple list items below the top-level key "modules". */
int yaml_count_modules(const char *filename);
#endif
