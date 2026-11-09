#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 10: sum valid scores\n");
    double sum = 0.0; size_t used = 0;
    int ok = json_sum_valid_scores(path, &sum, &used);
    printf("Success: %d, sum: %.2f, used: %zu\n", ok, sum, used);
    return 0;
}
