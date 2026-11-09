# Exercise 15 — Stable sort by numeric grade

**Difficulty:** Level 3 — Difficult  
**Points:** 3.0 pts  
**Function to implement:** `csv_sort_by_grade`

## Statement

Sort records by ascending grade while preserving the original order of records with equal grades. Keep the header at the top.

## Required prototype

```c
int csv_sort_by_grade(const char *input, const char *output);
```

## Suggested solution steps

1. Read records into an array of structs containing raw row text, parsed grade and original index.
2. Use insertion sort or merge sort; compare grade only and preserve ties.
3. Write the header, followed by sorted raw rows.
4. Check the maximum row count or grow the array with realloc safely.

## Useful predefined functions / library API

fgets, strtod, malloc, realloc, free, qsort (not stable by itself), fprintf

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Equal grades; empty data; malformed grade; capacity/allocation failure.

## Expected result for the supplied fixture

Dora, Bob, Ada, Cleo (Ada remains before Cleo).

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
