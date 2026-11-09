#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 15: count nodes\n");
    JsonStats stats = {0};
    int ok = json_count_nodes(path, &stats);
    printf("Success: %d, objects: %zu, arrays: %zu, max depth: %zu\n", ok, stats.objects, stats.arrays, stats.max_depth);
    return 0;
}
