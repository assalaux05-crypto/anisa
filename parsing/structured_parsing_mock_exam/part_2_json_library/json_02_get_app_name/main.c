#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 02: get app name\n");
    char name[128] = {0};
    int ok = json_get_app_name(path, name, sizeof(name));
    printf("Success: %d, app: %s\n", ok, name);
    return 0;
}
