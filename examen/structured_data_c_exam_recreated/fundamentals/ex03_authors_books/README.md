# Exercise 3 — parse author rows and search books — 15 points

**Remembered prototypes:**
```c
struct author *parse_author_row(char *row);
void print_all_books_written_by(char *author_lastname);
```

The file `authors.csv` contains `id,lastname`. The file `books.csv` contains `id,book,author_id`.

1. Define `struct author` (your notes may say `struct autor`; use the spelling in the supplied header) with `unsigned id` and dynamically allocated `char *name`.
2. `parse_author_row` receives one data row such as `2,Rowling`, parses the ID using `atoi`, duplicates the name, and returns a heap-allocated struct. Return NULL on invalid input/allocation failure.
3. `print_all_books_written_by` searches `authors.csv` for the requested last name, gets that author's ID, then scans `books.csv` and prints every book whose `author_id` matches.
4. Free every temporary field and author object. Do not include CSV headers in data parsing.

For this practice subset, values do not contain quoted commas. One book title per output line; preserve file order. If the author does not exist, print nothing.

Expected example for `print_all_books_written_by("Herbert")`:
```text
Dune
Dune Messiah
Children of Dune
```

The function intentionally uses the filenames in this directory, matching the remembered zero-path-argument prototype. A test main is supplied.
