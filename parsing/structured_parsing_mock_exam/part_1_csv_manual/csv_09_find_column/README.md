# Exercise 09 — Find a column by name even when column order changes

**Difficulty:** Level 2 — Medium  
**Points:** 2.0 pts  
**Function to implement:** `csv_find_column`

## Statement

Search the header and return the zero-based index of an exact column name.

## Required prototype

```c
int csv_find_column(const char *path, const char *name, size_t *column_index);
```

## Suggested solution steps

1. Read the header line.
2. Parse each header field and trim the line ending (do not silently trim meaningful spaces unless specified).
3. Compare with strcmp.
4. Return the first matching index; return 0 if absent.

## Useful predefined functions / library API

strcmp, strchr, strcspn or manual trim

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Unknown column; empty column name; duplicate header names; name at last index.

## Expected result for the supplied fixture

email column is 1.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
