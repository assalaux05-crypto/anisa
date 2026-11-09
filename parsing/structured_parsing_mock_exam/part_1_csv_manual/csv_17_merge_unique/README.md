# Exercise 17 — Merge two CSV files and deduplicate by ID

**Difficulty:** Level 3 — Difficult  
**Points:** 3.5 pts  
**Function to implement:** `csv_merge_unique`

## Statement

Both files have the same header. Write the header once, then each distinct ID in first-file order, followed by IDs from the second file that have not appeared before. Keep the first occurrence overall, including duplicates inside one input.

## Required prototype

```c
int csv_merge_unique(const char *first, const char *second, const char *output);
```

## Suggested solution steps

1. Validate that headers match exactly (field-by-field).
2. Read IDs from the first file and remember them.
3. Stream the second file and skip IDs already seen.
4. Write valid rows using correct CSV output escaping or preserve raw record text.

## Useful predefined functions / library API

fopen, strcmp, dynamic arrays, realloc, strtol, fclose

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Different headers; duplicate inside same file; empty files; duplicate ID; malformed row.

## Expected result for the supplied fixture

IDs 1, 2, 3 only; keep the first ID 2 record.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
