#include "exercise.h"
#include <stdio.h>
int main(void)
{
    Author a = {7, "Herbert", "USA"};
    if (json_write_author("author_out.json", &a) == 0)
        puts("Wrote author_out.json");
    else puts("json_write_author: TODO");
    return 0;
}
