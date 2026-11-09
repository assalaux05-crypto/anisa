#ifndef EXERCISE_H
#define EXERCISE_H
#include <stddef.h>
#include <yajl/yajl_tree.h>
typedef struct { int id; char name[64]; int grade; } Student;
int json_read_students(const char *path, Student *out, size_t capacity,
                       size_t *count);
#endif
