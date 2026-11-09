#include "exercise.h"
#include <stdio.h>
int main(void)
{
    FILE *file = fopen("fields.csv", "r");
    char row[256];
    if (!file) return 1;
    if (!fgets(row, sizeof(row), file)) { fclose(file); return 1; }
    while (fgets(row, sizeof(row), file)) {
        char *cursor = row;
        char *field;
        size_t column = 1;
        while ((field = parse_field(&cursor)) != NULL)
            printf("column %zu: %s\n", column++, field);
    }
    fclose(file);
    return 0;
}
