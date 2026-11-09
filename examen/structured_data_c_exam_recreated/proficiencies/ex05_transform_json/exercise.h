#ifndef EXERCISE_H
#define EXERCISE_H
#include <yajl/yajl_tree.h>
#include <yajl/yajl_gen.h>
typedef struct { int id; char title[96]; int pages; } Book;
int json_filter_books(const char *input, const char *output, int minimum_pages);
#endif
