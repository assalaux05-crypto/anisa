#ifndef EXERCISE_H
#define EXERCISE_H
#include <stddef.h>
#include <yajl/yajl_parse.h>
typedef struct { size_t strings, integers, arrays, objects; } JsonStats;
int json_count_events(const char *path, JsonStats *out);
#endif
