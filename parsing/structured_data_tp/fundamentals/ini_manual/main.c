#include "exercise.h"
#include <stdio.h>
int main(void)
{
    char value[128];
    if (ini_get("app.ini", "server", "host", value, sizeof(value)) == 0)
        printf("Host: %s\n", value);
    else
        puts("Host: not found");
    return 0;
}
