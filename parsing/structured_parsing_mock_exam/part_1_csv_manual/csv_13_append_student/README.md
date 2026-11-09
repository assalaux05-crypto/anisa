# Exercise 13 — Append a student safely

**Difficulty:** Level 2 — Medium  
**Points:** 2.5 pts  
**Function to implement:** `csv_append_student`

## Statement

Append one student record. Every field must be correctly escaped: quote fields containing comma, quote, CR or LF, and double embedded quotes.

## Required prototype

```c
int csv_append_student(const char *path, const CsvStudent *student);
```

## Suggested solution steps

1. Validate the struct fields.
2. Open in append mode and ensure an existing non-empty file ends with a record separator.
3. Write numeric fields, then write each text field through a CSV escaping helper.
4. Close and check ferror/fclose.

## Useful predefined functions / library API

fopen("a"), fputc, fputs, fprintf, strchr, fclose

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Name contains comma; quote; newline; empty field; file does not end with newline.

## Expected result for the supplied fixture

Dora, Jr. is written as "Dora, Jr.".

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
