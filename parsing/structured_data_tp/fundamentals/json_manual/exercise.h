#ifndef EXERCISE_H
#define EXERCISE_H
#include <stddef.h>
/* Extract the string value for a top-level key. Return 0 or -1. */
int json_get_string(const char *filename, const char *key, char *out, size_t out_size);
/* Extract a non-negative integer value for a top-level key. Return 0 or -1. */
int json_get_int(const char *filename, const char *key, int *out);
/* Count objects in the top-level "students" array. Return -1 on error. */
int json_count_students(const char *filename);
/* Change the top-level "semester" integer. Return 0 or -1. */
int json_update_semester(const char *filename, int semester);
#endif
