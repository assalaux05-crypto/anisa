#include <stdio.h>
#include <stddef.h>
#include "exercise.h"
#include <stdio.h>

int main(void)
{
    const char *path = "multiline.csv";
    (void)path;
    printf("Exercise 18: Read a logical record spanning multiple physical lines\n");
    FILE *fp = fopen("multiline.csv", "r"); CsvRecord record;
    if (fp) { while (csv_read_record(fp, &record)) printf("Record bytes: %zu\n", record.length); fclose(fp); }
    return 0;
}
