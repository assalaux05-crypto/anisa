#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "tes_data-header.csv";
    (void)path;
    printf("Exercise 05: Sum an integer column\n");
    long total;
    if (csv_sum_integer_column("data.csv", 4, &total))
        printf("Grade sum: %ld\n", total);
    return 0;
}
