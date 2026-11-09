# Exercise 01 — Count data records

**Difficulty:** Level 1 — Easy  
**Points:** 1.0 pts  
**Function to implement:** `csv_count_records`

## Statement

Count data records, excluding the header. Ignore completely empty lines. The file may end with or without a final newline.

## Required prototype

```c
size_t csv_count_records(const char *path);
```

## Suggested solution steps

1. Open the file with fopen(path, "r").
2. Read the first line as the header; if there is no line, return 0.
3. Read the remaining lines with fgets and count only lines that contain a non-whitespace character.
4. Always close the file, including error paths.

## Useful predefined functions / library API

fopen, fgets, fclose, isspace

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Missing file; empty file; header only; blank lines; final line without \n.

## Expected result for the supplied fixture

3 data records.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
