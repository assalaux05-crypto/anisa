# Exercise 06 — Find a student and fill a C struct

**Difficulty:** Level 2 — Medium  
**Points:** 2.0 pts  
**Function to implement:** `csv_find_student`

## Statement

Search by id and copy the matching row into CsvStudent. The struct is declared in exercise.h. Return 1 when found, 0 otherwise.

## Required prototype

```c
int csv_find_student(const char *path, int wanted_id, CsvStudent *out);
```

## Suggested solution steps

1. Define and initialize a local CsvStudent.
2. Read each row and extract its four fields.
3. Convert id and grade safely; copy strings with bounded copying.
4. When the id matches, assign the fully checked temporary struct to *out.

## Useful predefined functions / library API

fgets, strcmp, strtol, strtod, snprintf, sizeof

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

ID not found; malformed row; long name; duplicate IDs (return the first match).

## Expected result for the supplied fixture

ID 2 returns Bob, Math, 14.0.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
