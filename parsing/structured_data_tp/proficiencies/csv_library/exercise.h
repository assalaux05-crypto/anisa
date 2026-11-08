#ifndef EXERCISE_H
#define EXERCISE_H
#include <stddef.h>
struct student { int id; char name[64]; int grade; };
/* Parse CSV with libcsv and return the number of valid student records. */
int csv_library_count(const char *filename);
/* Find id and fill out. Return 0 or -1. */
int csv_library_find(const char *filename, int id, struct student *out);
/* Compute the average grade, or -1.0 on error/empty file. */
double csv_library_average(const char *filename);
/* Write students whose grade is >= minimum to output using valid CSV escaping. */
int csv_library_filter(const char *input, const char *output, int minimum);
#endif
