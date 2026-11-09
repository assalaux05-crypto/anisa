#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 12: Delete a record by ID\n");
    printf("Delete: %s\n", csv_remove_student("data.csv", "without_bob.csv", 2) ? "success" : "not found/error");
    return 0;
}
