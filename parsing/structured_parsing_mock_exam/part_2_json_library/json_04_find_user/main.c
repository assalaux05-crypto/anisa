#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 04: find user\n");
    JsonUser user = {0};
    int ok = json_find_user(path, 8, &user);
    printf("Success: %d, user: %s, active: %d\n", ok, user.name, user.active);
    return 0;
}
