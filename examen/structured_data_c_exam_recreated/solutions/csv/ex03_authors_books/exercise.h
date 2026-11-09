#ifndef EXERCISE_H
#define EXERCISE_H
typedef struct author { unsigned id; char *name; } author;
struct author *parse_author_row(char *row);
void print_all_books_written_by(char *author_lastname);
void free_author(struct author *value);
#endif
