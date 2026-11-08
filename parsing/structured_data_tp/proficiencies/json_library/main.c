#include "exercise.h"
#include <stdio.h>
int main(void)
{
    printf("Courses: %d\n", json_library_count_courses("courses.json"));
    printf("Students: %d\n", json_library_total_students("courses.json"));
    return 0;
}
