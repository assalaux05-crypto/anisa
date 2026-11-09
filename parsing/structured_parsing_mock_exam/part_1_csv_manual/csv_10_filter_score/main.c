#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 10: Filter records by a numeric score\n");
    printf("Written rows: %s\n", csv_filter_score("data.csv", "filtered.csv", 15.0) ? "success" : "failure");
    return 0;
}
