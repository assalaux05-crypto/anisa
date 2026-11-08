#ifndef EXERCISE_H
#define EXERCISE_H
/* Open the database, count students, and close it. Return -1 on error. */
int sql_count_students(const char *filename);
/* Insert one student using a prepared statement. Return 0 or -1. */
int sql_add_student(const char *filename, int id, const char *name, int grade);
/* Update a student's grade. Return 0 or -1. */
int sql_update_grade(const char *filename, int id, int grade);
/* Delete a student. Return 0 or -1. */
int sql_delete_student(const char *filename, int id);
#endif
