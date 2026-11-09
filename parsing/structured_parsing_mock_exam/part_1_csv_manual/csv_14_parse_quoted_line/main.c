#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "quoted.csv";
    (void)path;
    printf("Exercise 14: Parse a quoted CSV record\n");
    CsvField fields[8]; size_t count = 0;
    if (csv_parse_quoted_line("7,\"Doe, Jane\",\"He said \"\"hello\"\"\"", fields, 8, &count))
        printf("Parsed fields: %zu\n", count);
    return 0;
}
