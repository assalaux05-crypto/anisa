#include "exercise.h"
#include <stdio.h>
int main(void)
{
    char row[] = "2,Rowling";
    struct author *a = parse_author_row(row);
    if (a) {
        printf("author: id=%u name=%s\n", a->id, a->name);
        free_author(a);
    } else {
        puts("parse_author_row: not implemented / invalid row");
    }
    puts("Books by Herbert:");
    print_all_books_written_by("Herbert");
    return 0;
}
