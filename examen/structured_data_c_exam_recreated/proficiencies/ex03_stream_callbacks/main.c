#include "exercise.h"
#include <stdio.h>
int main(void)
{
    JsonStats s = {0};
    if (json_count_events("stats.json", &s) == 0)
        printf("strings=%zu integers=%zu arrays=%zu objects=%zu\n",
               s.strings, s.integers, s.arrays, s.objects);
    else puts("json_count_events: TODO");
    return 0;
}
