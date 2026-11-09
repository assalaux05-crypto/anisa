#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 18: roundtrip courses\n");
    int ok = json_roundtrip_courses(path, "roundtrip.json");
    printf("Round trip: %d\n", ok);
    return 0;
}
