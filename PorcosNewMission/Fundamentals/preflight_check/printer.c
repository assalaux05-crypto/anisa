#include <stdio.h>
#include <stdlib.h>

#include "fibo.h"
#include "hello_world.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <n> [name]\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    printf("%d\n", fibo(n));

    char *name = argc > 2 ? argv[2] : NULL;
    hello_world(name);

    return 0;
}
