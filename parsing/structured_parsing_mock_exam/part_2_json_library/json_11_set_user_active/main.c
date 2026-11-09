#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 11: set user active\n");
    int ok = json_set_user_active(path, "modified.json", 1, 1);
    printf("Update: %d\n", ok);
    return 0;
}
