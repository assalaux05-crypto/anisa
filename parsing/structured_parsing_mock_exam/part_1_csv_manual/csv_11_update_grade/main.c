#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 11: Update one student record\n");
    printf("Update: %s\n", csv_update_grade("data.csv", "updated.csv", 2, 18.5) ? "success" : "not found/error");
    return 0;
}
