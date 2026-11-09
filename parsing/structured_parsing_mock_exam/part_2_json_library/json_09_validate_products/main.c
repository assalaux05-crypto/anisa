#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 09: validate products\n");
    size_t bad = 0; char message[128] = {0};
    int ok = json_validate_products(path, &bad, message, sizeof(message));
    printf("Valid: %d, bad index: %zu, reason: %s\n", ok, bad, message);
    return 0;
}
