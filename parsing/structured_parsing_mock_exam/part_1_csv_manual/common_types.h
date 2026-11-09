#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H
#include <stddef.h>
#include <stdio.h>

#define CSV_TEXT_MAX 128
#define CSV_MAX_FIELDS 16
#define CSV_RECORD_MAX 4096

typedef struct {
    int id;
    char name[64];
    char department[64];
    double grade;
} CsvStudent;

typedef struct {
    char value[CSV_TEXT_MAX];
} CsvField;

typedef struct {
    char text[CSV_RECORD_MAX];
    size_t length;
} CsvRecord;

#endif
