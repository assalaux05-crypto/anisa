#ifndef EXERCISE_H
#define EXERCISE_H
#include <stddef.h>
#include <yajl/yajl_tree.h>
typedef struct { char host[64]; int port; int debug; } ServerConfig;
int json_read_config(const char *path, ServerConfig *out);
#endif
