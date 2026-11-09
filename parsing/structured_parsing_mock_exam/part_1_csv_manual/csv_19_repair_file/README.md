# Exercise 19 — Recover valid rows from a damaged CSV file

**Difficulty:** Level 4 — Expert  
**Points:** 4.0 pts  
**Function to implement:** `csv_repair_file`

## Statement

Write the header and every valid row to output. A valid row has valid CSV quoting and exactly the header number of fields. Count rejected data records. This exercise tests error recovery; do not crash or loop forever on malformed input.

## Required prototype

```c
size_t csv_repair_file(const char *input, const char *output, size_t *rejected);
```

## Suggested solution steps

1. Read logical records with a state machine.
2. Validate quote syntax and field count for each record.
3. Write valid records exactly once.
4. For an invalid record, increment rejected and continue at the next recoverable record boundary.
5. Close files and return the number of kept rows.

## Useful predefined functions / library API

fgetc, dynamic buffer or fixed bounded buffer, fopen, fputs, fclose

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Unclosed quote; extra/missing fields; blank row; malformed row followed by valid row; too-long record.

## Expected result for the supplied fixture

Keep IDs 1 and 4; reject the two malformed records.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
