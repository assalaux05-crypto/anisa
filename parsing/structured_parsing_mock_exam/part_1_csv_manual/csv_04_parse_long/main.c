#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 04: Convert a field into an integer safely\n");
    long number;
    if (csv_parse_long("42 ", &number))
        printf("Parsed integer: %ld\n", number);
    return 0;
}
