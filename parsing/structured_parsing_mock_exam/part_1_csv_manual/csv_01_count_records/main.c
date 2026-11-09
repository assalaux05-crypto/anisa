#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 01: Count data records\n");
    printf("Data records: %zu\n", csv_count_records("data.csv"));
    return 0;
}
