#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 13: Append a student safely\n");
    CsvStudent s = {4, "Dora, Jr.", "Robotics", 18.0};
    printf("Append: %s\n", csv_append_student("data.csv", &s) ? "success" : "failure");
    return 0;
}
