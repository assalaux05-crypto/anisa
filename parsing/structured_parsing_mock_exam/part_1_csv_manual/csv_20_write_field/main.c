#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.csv";
    (void)path;
    printf("Exercise 20: Write one CSV field with correct escaping\n");
    FILE *fp = fopen("field.txt", "w");
    if (fp) { csv_write_field(fp, "Dora, Jr."); fputc(10, fp); fclose(fp); }
    return 0;
}
