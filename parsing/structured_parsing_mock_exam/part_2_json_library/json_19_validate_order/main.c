#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 19: validate order\n");
    char error_path[128] = {0};
    int ok = json_validate_order(path, error_path, sizeof(error_path));
    printf("Valid: %d, error path: %s\n", ok, error_path);
    return 0;
}
