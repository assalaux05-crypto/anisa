#ifndef EXERCISE_14_H
#define EXERCISE_14_H

#include "../common_types.h"

int csv_parse_quoted_line(const char *line, CsvField *fields, size_t capacity, size_t *field_count);

#endif
