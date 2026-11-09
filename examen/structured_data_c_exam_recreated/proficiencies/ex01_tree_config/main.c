#include "exercise.h"
#include <stdio.h>
int main(void)
{
    ServerConfig c = {0};
    if (json_read_config("config.json", &c) == 0)
        printf("%s:%d debug=%d\n", c.host, c.port, c.debug);
    else puts("json_read_config: not implemented / invalid JSON");
    return 0;
}
