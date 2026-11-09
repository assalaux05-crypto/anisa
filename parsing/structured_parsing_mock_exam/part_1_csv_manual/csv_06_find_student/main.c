#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 06: Find a student and fill a C struct\n");
    CsvStudent student;
    if (csv_find_student("data.csv", 2, &student))
        printf("%s: %.1f\n", student.name, student.grade);
    return 0;
}
