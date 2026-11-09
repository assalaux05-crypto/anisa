#include "exercise.h"
#include <stdio.h>
int main(void)
{
    Student students[8] = {{0}};
    size_t count = 0;
    if (json_read_students("students.json", students, 8, &count) != 0) {
        puts("json_read_students: not implemented / invalid JSON");
        return 0;
    }
    for (size_t i = 0; i < count; i++)
        printf("%d %s %d\n", students[i].id, students[i].name, students[i].grade);
    return 0;
}
