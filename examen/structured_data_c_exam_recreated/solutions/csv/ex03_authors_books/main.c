#include "exercise.h"
#include <stdio.h>
int main(void)
{
    char row[] = "2,Rowling";
    struct author *value = parse_author_row(row);
    if (!value) return 1;
    printf("parsed author: %u %s\n", value->id, value->name);
    free_author(value);
    puts("Books by Herbert:");
    print_all_books_written_by("Herbert");
    return 0;
}
