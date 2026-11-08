#include "exercise.h"
#include <stdio.h>
int main(void)
{
    char course[64];
    int year;
    if (json_get_string("course.json", "course", course, sizeof(course)) == 0)
        printf("Course: %s\n", course);
    if (json_get_int("course.json", "year", &year) == 0)
        printf("Year: %d\n", year);
    printf("Students: %d\n", json_count_students("course.json"));
    return 0;
}
