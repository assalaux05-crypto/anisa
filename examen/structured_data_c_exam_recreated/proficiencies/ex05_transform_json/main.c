#include "exercise.h"
#include <stdio.h>
int main(void)
{
    if (json_filter_books("books.json", "long_books.json", 250) == 0)
        puts("Wrote long_books.json");
    else puts("json_filter_books: TODO");
    return 0;
}
