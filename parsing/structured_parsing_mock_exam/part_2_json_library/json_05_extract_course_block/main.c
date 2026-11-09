#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 05: extract course block\n");
    JsonCourse course = {0};
    int ok = json_extract_course_block(path, 10, &course);
    printf("Success: %d, course: %s, students: %zu\n", ok, course.title, course.student_count);
    return 0;
}
