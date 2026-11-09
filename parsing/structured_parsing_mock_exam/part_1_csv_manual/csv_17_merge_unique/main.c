#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 17: Merge two CSV files and deduplicate by ID\n");
    printf("Merge: %s\n", csv_merge_unique("first.csv", "second.csv", "merged.csv") ? "success" : "failure");
    return 0;
}
