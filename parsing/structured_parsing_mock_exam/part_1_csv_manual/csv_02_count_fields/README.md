# Exercise 02 — Count columns in the header

**Difficulty:** Level 1 — Easy  
**Points:** 1.0 pts  
**Function to implement:** `csv_count_fields`

## Statement

Return the number of comma-separated columns in the first line. For this first exercise, assume the header contains no quoted commas.

## Required prototype

```c
size_t csv_count_fields(const char *path);
```

## Suggested solution steps

1. Open the file and read only the first line.
2. An empty header has zero fields; otherwise the number of fields is commas + 1.
3. Do not count commas after the line terminator.
4. Close the file and return 0 on open/read failure.

## Useful predefined functions / library API

fopen, fgets, strchr or a for loop, fclose

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

One-column header; empty file; trailing comma (it means an empty last field).

## Expected result for the supplied fixture

4 header fields.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
