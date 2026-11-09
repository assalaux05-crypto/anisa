# Exercise 05 — Sum an integer column

**Difficulty:** Level 1 — Easy  
**Points:** 2.0 pts  
**Function to implement:** `csv_sum_integer_column`

## Statement

Sum all values from a zero-based column. All data values in that column are valid integers. Return 1 on success and 0 on any file/column/conversion error.

## Required prototype

```c
int csv_sum_integer_column(const char *path, size_t column, long *sum);
```

## Suggested solution steps

1. Read and skip the header.
2. For each record, extract the requested field.
3. Convert with your csv_parse_long logic (you may copy the helper into this folder).
4. Check the column exists in every row and protect the sum from overflow.

## Useful predefined functions / library API

fopen, fgets, strtol, errno, LONG_MAX, LONG_MIN, fclose

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

No data rows; invalid column; empty value; negative numbers; sum overflow.

## Expected result for the supplied fixture

For data.csv, points sum to 35.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
