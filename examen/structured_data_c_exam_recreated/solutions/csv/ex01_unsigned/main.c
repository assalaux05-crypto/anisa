#include "exercise.h"
#include <stdio.h>
#include <string.h>
int main(void)
{
    FILE *file = fopen("units.csv", "r");
    char line[128];
    if (!file) return 1;
    if (!fgets(line, sizeof(line), file)) { fclose(file); return 1; }
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = '\0';
        printf("%s -> %u\n", line, parse_unit(line));
    }
    fclose(file);
    return 0;
}
