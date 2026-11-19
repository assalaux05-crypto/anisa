#include <stdint.h>
#include <stdio.h>

#define N 100000
#define ITERATIONS 1000

static uint32_t data[N];

uint32_t compute(void)
{
    uint32_t result = 0;

    for (int i = 0; i < N; i++)
    {
        uint32_t x = data[i];

        for (int j = 0; j < ITERATIONS; j++)
            x = x * 1664525u + 1013904223u;

        result ^= x;
    }

    return result;
}

int main(void)
{
    for (int i = 0; i < N; i++)
        data[i] = (uint32_t)i;

    printf("%u\n", compute());
    return 0;
}
