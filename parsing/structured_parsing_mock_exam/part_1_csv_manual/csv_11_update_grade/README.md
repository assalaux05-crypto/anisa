# Exercise 11 — Update one student record

**Difficulty:** Level 2 — Medium  
**Points:** 2.5 pts  
**Function to implement:** `csv_update_grade`

## Statement

Copy the CSV to a new file while replacing the grade of the row with the requested id. Do not modify the input file.

## Required prototype

```c
int csv_update_grade(const char *input, const char *output, int id, double new_grade);
```

## Suggested solution steps

1. Read the header and locate id and grade columns.
2. Parse every row and compare the id.
3. Write every row to output; for the matching row, replace only the grade field.
4. Return failure if the id was not found; remove incomplete output on error if possible.

## Useful predefined functions / library API

fopen, fgets, fprintf, snprintf, strtol, strtod, remove

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

ID absent; multiple matches (update first only); malformed row; output creation failure.

## Expected result for the supplied fixture

Bob grade becomes 18.5; other rows remain unchanged.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
