#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "malformed.json";
    (void)path;
    printf("Exercise 16: report parse error\n");
    char message[256] = {0};
    int ok = json_report_parse_error(path, message, sizeof(message));
    printf("Valid: %d, message: %s\n", ok, message);
    return 0;
}
