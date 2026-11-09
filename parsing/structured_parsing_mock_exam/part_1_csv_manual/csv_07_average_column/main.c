#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 07: Average a column selected by header name\n");
    double average; size_t used;
    if (csv_average_column("data.csv", "grade", &average, &used))
        printf("Average: %.2f (%zu rows)\n", average, used);
    return 0;
}
