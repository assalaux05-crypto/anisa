#include "exercise.h"
#include <stdio.h>
int main(void)
{
    printf("Valid students: %d\n", csv_library_count("students.csv"));
    printf("Average: %.2f\n", csv_library_average("students.csv"));
    return 0;
}
