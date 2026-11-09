#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "left.json";
    (void)path;
    printf("Exercise 17: merge people\n");
    int ok = json_merge_people("left.json", "right.json", "merged.json");
    printf("Merge: %d\n", ok);
    return 0;
}
