# Exercise 10 — Filter records by a numeric score

**Difficulty:** Level 2 — Medium  
**Points:** 2.5 pts  
**Function to implement:** `csv_filter_score`

## Statement

Write the original header and only records whose score is greater than or equal to min_score. The score column is named score.

## Required prototype

```c
int csv_filter_score(const char *input, const char *output, double min_score);
```

## Suggested solution steps

1. Open input for reading and output for writing; handle both failures.
2. Find the score column from the header.
3. For each data record, parse score and decide whether to copy it.
4. Close both files and return success only if all I/O operations succeeded.

## Useful predefined functions / library API

fopen, fgets, fputs, fprintf, strtod, fclose

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

No qualifying rows; threshold exactly equals score; output path equals input (must reject or use a temp file).

## Expected result for the supplied fixture

Keeps Ada, Cleo and Dora for threshold 15.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
