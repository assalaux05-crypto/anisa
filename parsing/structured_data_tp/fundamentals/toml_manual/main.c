#include "exercise.h"
#include <stdio.h>
int main(void)
{
    char host[64];
    if (toml_get("settings.toml", "database", "host", host, sizeof(host)) == 0)
        printf("Host: %s\n", host);
    return 0;
}
