# Exercise 18 — Read a logical record spanning multiple physical lines

**Difficulty:** Level 4 — Expert  
**Points:** 4.0 pts  
**Function to implement:** `csv_read_record`

## Statement

Read one complete logical CSV record. A newline ends a record only when the parser is outside a quoted field. Preserve the original bytes in record.text and set record.length.

## Required prototype

```c
int csv_read_record(FILE *stream, CsvRecord *record);
```

## Suggested solution steps

1. Read character-by-character using fgetc.
2. Track whether you are inside a quoted field.
3. Inside quotes, treat doubled quotes as escaped quotes.
4. Stop at newline only outside quotes; handle EOF and unterminated quotes.
5. Reject record-buffer overflow without writing past the array.

## Useful predefined functions / library API

fgetc, feof, ferror, clearerr, size_t bounds

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Embedded newline; escaped quote; CRLF; EOF without final newline; unclosed quote; buffer full.

## Expected result for the supplied fixture

The comment for ID 1 is one record even though it occupies two lines.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
