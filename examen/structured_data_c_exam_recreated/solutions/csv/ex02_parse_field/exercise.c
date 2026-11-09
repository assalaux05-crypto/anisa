#include "exercise.h"
#include <stddef.h>
char *parse_field(char **input)
{
    char *field;
    char *end;
    if (input == NULL || *input == NULL)
        return NULL;
    field = *input;
    end = field;
    while (*end != '\0' && *end != ',' && *end != '\n' && *end != '\r')
        end++;
    if (*end == ',') {
        *end = '\0';
        *input = end + 1;
    } else {
        *end = '\0';
        *input = NULL;
    }
    return field;
}
