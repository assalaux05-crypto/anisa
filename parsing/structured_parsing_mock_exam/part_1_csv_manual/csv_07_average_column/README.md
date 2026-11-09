# Exercise 07 — Average a column selected by header name

**Difficulty:** Level 2 — Medium  
**Points:** 2.0 pts  
**Function to implement:** `csv_average_column`

## Statement

Find the column by its header text, convert every non-empty value to double, and compute the average. Reject malformed non-empty numbers. Return 0 if no numeric values exist.

## Required prototype

```c
int csv_average_column(const char *path, const char *header, double *average, size_t *used_rows);
```

## Suggested solution steps

1. Parse the header and locate the exact column name.
2. For each row, extract that column.
3. Use strtod with endptr and errno checks.
4. Accumulate sum and count, then divide only when count > 0.

## Useful predefined functions / library API

strcmp, strtod, errno, ERANGE, isspace

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Column is not first; unknown header; empty cell; no rows; malformed decimal.

## Expected result for the supplied fixture

Average grade is 16.00 across 3 rows.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
