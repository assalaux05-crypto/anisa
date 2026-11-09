#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 01: count courses\n");
    size_t count = 0;
    int ok = json_count_courses(path, &count);
    printf("Success: %d, courses: %zu\n", ok, count);
    return 0;
}
