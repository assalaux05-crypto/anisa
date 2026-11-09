#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "damaged.csv";
    (void)path;
    printf("Exercise 19: Recover valid rows from a damaged CSV file\n");
    size_t rejected = 0;
    size_t kept = csv_repair_file("damaged.csv", "repaired.csv", &rejected);
    printf("Kept: %zu, rejected: %zu\n", kept, rejected);
    return 0;
}
