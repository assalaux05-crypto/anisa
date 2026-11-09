# Exercise 12 — Delete a record by ID

**Difficulty:** Level 2 — Medium  
**Points:** 2.5 pts  
**Function to implement:** `csv_remove_student`

## Statement

Write the header and all records except the first record whose id matches. Leave the source untouched.

## Required prototype

```c
int csv_remove_student(const char *input, const char *output, int id);
```

## Suggested solution steps

1. Read the header; find the id column.
2. For each row, parse the id.
3. Skip the first matching row and copy the others.
4. Report whether a row was removed and close all streams.

## Useful predefined functions / library API

fopen, fgets, fputs, strtol, fclose

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Deleting first/last/only row; missing ID; duplicate IDs; malformed row.

## Expected result for the supplied fixture

Output contains Ada and Cleo.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
