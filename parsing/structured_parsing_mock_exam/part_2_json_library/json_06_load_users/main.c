#include <stdio.h>
#include <stddef.h>
#include "exercise.h"
#include <stdlib.h>

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 06: load users\n");
    JsonUser *users = NULL; size_t count = 0;
    int ok = json_load_users(path, &users, &count);
    printf("Success: %d, users: %zu\n", ok, count);
    free(users);
    return 0;
}
