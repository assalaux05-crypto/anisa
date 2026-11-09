#ifndef EXERCISE_H
#define EXERCISE_H
#include <yajl/yajl_gen.h>
typedef struct { unsigned id; const char *lastname; const char *country; } Author;
int json_write_author(const char *path, const Author *author);
#endif
