# Exercise 08 — Validate that every record has the same number of fields

**Difficulty:** Level 2 — Medium  
**Points:** 2.0 pts  
**Function to implement:** `csv_validate_consistent_rows`

## Statement

Return 1 only when every non-empty data record has exactly the same field count as the header. On failure, write the one-based data-record number to bad_record.

## Required prototype

```c
int csv_validate_consistent_rows(const char *path, size_t *bad_record);
```

## Suggested solution steps

1. Count header fields.
2. Parse every non-empty record and count fields without losing empty trailing fields.
3. Compare each count with the header count.
4. Stop at the first invalid record and report its data-record index.

## Useful predefined functions / library API

fgetc or fgets, strchr, manual loops

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Missing field; extra field; empty field still counts; blank record; trailing comma.

## Expected result for the supplied fixture

Invalid: first bad data record is 2.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
