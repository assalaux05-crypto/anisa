# Exercise 16 — Calculate an average for one department

**Difficulty:** Level 3 — Difficult  
**Points:** 3.0 pts  
**Function to implement:** `csv_department_average`

## Statement

Find department and grade columns by header. Average only rows with an exact department match.

## Required prototype

```c
int csv_department_average(const char *path, const char *department, double *average, size_t *count);
```

## Suggested solution steps

1. Locate the two required columns by name.
2. Parse each row with the CSV field parser.
3. Compare department exactly and parse its grade.
4. Accumulate sum/count; fail if no matching valid row exists.

## Useful predefined functions / library API

strcmp, strtod, manual CSV parser

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Department not found; field order changed; whitespace; quoted department; no matching rows.

## Expected result for the supplied fixture

CS average is 18.00 across 3 records.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
