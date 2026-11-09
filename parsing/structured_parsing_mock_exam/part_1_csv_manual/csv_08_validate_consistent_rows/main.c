#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 08: Validate that every record has the same number of fields\n");
    size_t bad = 0;
    printf("Valid: %s\n", csv_validate_consistent_rows("data.csv", &bad) ? "yes" : "no");
    printf("First bad data record: %zu\n", bad);
    return 0;
}
