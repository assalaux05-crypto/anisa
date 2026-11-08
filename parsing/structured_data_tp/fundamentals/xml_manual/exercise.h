#ifndef EXERCISE_H
#define EXERCISE_H
#include <stddef.h>
/* Extract text from the first simple <name>...</name> element. */
int xml_get_text(const char *filename, const char *name, char *out, size_t out_size);
/* Count occurrences of a simple opening tag <student>. */
int xml_count_students(const char *filename);
/* Replace the text of the first simple element. */
int xml_set_text(const char *filename, const char *name, const char *value);
#endif
