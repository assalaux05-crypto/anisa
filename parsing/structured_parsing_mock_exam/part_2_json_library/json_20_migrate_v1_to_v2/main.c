#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 20: migrate v1 to v2\n");
    int ok = json_migrate_v1_to_v2(path, "migrated.json");
    printf("Migration: %d\n", ok);
    return 0;
}
