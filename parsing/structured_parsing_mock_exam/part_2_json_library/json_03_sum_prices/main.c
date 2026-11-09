#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 03: sum prices\n");
    double sum = 0.0;
    int ok = json_sum_prices(path, &sum);
    printf("Success: %d, total: %.2f\n", ok, sum);
    return 0;
}
