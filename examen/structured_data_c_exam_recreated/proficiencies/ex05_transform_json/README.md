# JSON Exercise 5 — filter and serialize — 10 points

Read `books.json`, keep only books with `pages >= minimum_pages`, and write a new JSON array to the output file. This exercise combines tree parsing, validation, C data handling and generator serialization.

```c
typedef struct { int id; char title[96]; int pages; } Book;
int json_filter_books(const char *input, const char *output, int minimum_pages);
```

Suggested solution: parse the input tree, locate the books array, validate each book, then generate the output array. For each retained object: `yajl_gen_map_open`, emit the `id`, `title`, `pages` keys and values, `yajl_gen_map_close`. Finish with `yajl_gen_array_close`, fetch buffer and write. Do not try to modify the YAJL tree using imaginary `set` functions.
