#include "exercise.h"
#include <stdio.h>
int main(void)
{
    char name[64];
    printf("Rows: %d\n", csv_count_rows("students.csv"));
    if (csv_find_student("students.csv", 2, name, sizeof(name)) == 0)
        printf("Student 2: %s\n", name);
    else
        puts("Student 2: not found");
    return 0;
}
