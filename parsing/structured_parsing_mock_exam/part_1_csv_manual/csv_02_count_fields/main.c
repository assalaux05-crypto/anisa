#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 02: Count columns in the header\n");
    printf("Header fields: %zu\n", csv_count_fields("data.csv"));
    return 0;
}
