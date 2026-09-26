#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Contact
{
    char *name;
    struct Contact *next;
};

void insert_contact(struct Contact **head, size_t index, char *name);
void remove_contact(struct Contact **head, size_t index);
void print_book(struct Contact *head);
void destroy_book(struct Contact *head);

#endif // ADDRESS_BOOK_H
