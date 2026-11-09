#include "exercise.h"
#include <stdio.h>
int main(void)
{
    FILE *file = fopen("fields.csv", "r");
    char row[256];
    if (!file) { perror("fields.csv"); return 1; }
    if (!fgets(row, sizeof(row), file)) { fclose(file); return 1; }
    while (fgets(row, sizeof(row), file)) {
        char *cursor = row;
        char *field;
        size_t index = 1;
        while ((field = parse_field(&cursor)) != NULL)
            printf("field %zu = [%s]\n", index++, field);
    }
    fclose(file);
    return 0;
}
