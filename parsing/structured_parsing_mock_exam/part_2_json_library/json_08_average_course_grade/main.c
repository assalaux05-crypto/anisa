#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 08: average course grade\n");
    double average = 0.0; size_t count = 0;
    int ok = json_average_course_grade(path, 2, &average, &count);
    printf("Success: %d, average: %.2f, count: %zu\n", ok, average, count);
    return 0;
}
