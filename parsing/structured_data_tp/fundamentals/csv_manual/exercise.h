#ifndef EXERCISE_H
#define EXERCISE_H
#include <stddef.h>
/* Return number of data rows (not counting the header), or -1 on error. */
int csv_count_rows(const char *filename);
/* Find a student by id. Copy the name into out; return 0, -1 if absent/error. */
int csv_find_student(const char *filename, int id, char *out, size_t out_size);
/* Append a student. Return 0 on success, -1 on error. */
int csv_add_student(const char *filename, int id, const char *name, int grade);
/* Replace the grade of the student with id. Return 0, -1 if not found/error. */
int csv_update_grade(const char *filename, int id, int grade);
/* Remove the student with id. Return 0, -1 if not found/error. */
int csv_delete_student(const char *filename, int id);
#endif
