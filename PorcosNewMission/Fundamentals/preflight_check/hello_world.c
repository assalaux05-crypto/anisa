#include "hello_world.h"

#include <stdio.h>

void hello_world(char *str)
{
    if (str == NULL || str[0] == '\0')
        str = "World";

    printf("Hello, %s !\n", str);
}
