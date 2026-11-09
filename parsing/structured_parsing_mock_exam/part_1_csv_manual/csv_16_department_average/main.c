#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 16: Calculate an average for one department\n");
    double avg; size_t n;
    if (csv_department_average("data.csv", "CS", &avg, &n))
        printf("CS average: %.2f (%zu)\n", avg, n);
    return 0;
}
