#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 09: Find a column by name even when column order changes\n");
    size_t index;
    if (csv_find_column("data.csv", "email", &index))
        printf("email column: %zu\n", index);
    return 0;
}
