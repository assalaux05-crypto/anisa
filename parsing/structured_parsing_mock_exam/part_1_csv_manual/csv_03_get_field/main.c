#include <stdio.h>
#include <stddef.h>
#include "exercise.h"


int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 03: Extract a field from a simple CSV line\n");
    char field[64];
    if (csv_get_field("12,Manel,Algiers", 5, field, sizeof(field)))
        printf("Field 1: %s\n", field);
    return 0;
}
