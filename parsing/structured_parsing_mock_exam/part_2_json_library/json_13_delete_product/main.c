#include <stdio.h>
#include <stddef.h>
#include "exercise.h"

int main(void)
{
    const char *path = "data.json";
    (void)path;
    printf("Exercise 13: delete product\n");
    int ok = json_delete_product(path, "without_product.json", 2);
    printf("Delete: %d\n", ok);
    return 0;
}
