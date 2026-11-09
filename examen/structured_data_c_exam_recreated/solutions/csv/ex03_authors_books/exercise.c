#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *next_field(char **cursor)
{
    char *field;
    char *end;
    if (cursor == NULL || *cursor == NULL)
        return NULL;
    field = *cursor;
    end = field;
    while (*end != '\0' && *end != ',' && *end != '\n' && *end != '\r')
        end++;
    if (*end == ',') {
        *end = '\0';
        *cursor = end + 1;
    } else {
        *end = '\0';
        *cursor = NULL;
    }
    return field;
}

static int is_unsigned_decimal(const char *text)
{
    size_t i;
    if (text == NULL || text[0] == '\0')
        return 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (!isdigit((unsigned char)text[i]))
            return 0;
    }
    return 1;
}

struct author *parse_author_row(char *row)
{
    char *cursor = row;
    char *id_text;
    char *name;
    struct author *result;
    size_t name_len;
    if (row == NULL)
        return NULL;
    id_text = next_field(&cursor);
    name = next_field(&cursor);
    if (id_text == NULL || name == NULL || cursor != NULL ||
        !is_unsigned_decimal(id_text) || name[0] == '\0')
        return NULL;
    result = malloc(sizeof(*result));
    if (result == NULL)
        return NULL;
    name_len = strlen(name);
    result->name = malloc(name_len + 1);
    if (result->name == NULL) {
        free(result);
        return NULL;
    }
    result->id = (unsigned)atoi(id_text);
    memcpy(result->name, name, name_len + 1);
    return result;
}

void free_author(struct author *value)
{
    if (value != NULL) {
        free(value->name);
        free(value);
    }
}

void print_all_books_written_by(char *author_lastname)
{
    FILE *authors;
    FILE *books;
    char line[512];
    unsigned author_id = 0;
    int found = 0;
    if (author_lastname == NULL)
        return;
    authors = fopen("authors.csv", "r");
    if (authors == NULL)
        return;
    if (fgets(line, sizeof(line), authors) == NULL) {
        fclose(authors);
        return;
    }
    while (fgets(line, sizeof(line), authors) != NULL) {
        struct author *value = parse_author_row(line);
        if (value != NULL && strcmp(value->name, author_lastname) == 0) {
            author_id = value->id;
            found = 1;
            free_author(value);
            break;
        }
        free_author(value);
    }
    fclose(authors);
    if (!found)
        return;
    books = fopen("books.csv", "r");
    if (books == NULL)
        return;
    if (fgets(line, sizeof(line), books) == NULL) {
        fclose(books);
        return;
    }
    while (fgets(line, sizeof(line), books) != NULL) {
        char *cursor = line;
        char *book_id = next_field(&cursor);
        char *title = next_field(&cursor);
        char *author_id_text = next_field(&cursor);
        if (book_id != NULL && title != NULL && author_id_text != NULL &&
            is_unsigned_decimal(author_id_text) &&
            (unsigned)atoi(author_id_text) == author_id)
            printf("%s\n", title);
    }
    fclose(books);
}
