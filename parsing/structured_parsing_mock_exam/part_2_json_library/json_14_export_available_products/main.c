#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 14: export available products\n");
    int ok = json_export_available_products(path, "available.json");
    printf("Filter: %d\n", ok);
    return 0;
}
