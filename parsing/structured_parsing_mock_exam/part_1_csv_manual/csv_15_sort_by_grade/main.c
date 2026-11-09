#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 15: Stable sort by numeric grade\n");
    printf("Sorted: %s\n", csv_sort_by_grade("data.csv", "sorted.csv") ? "success" : "failure");
    return 0;
}
