# Exercise 14 — Parse a quoted CSV record

**Difficulty:** Level 3 — Difficult  
**Points:** 3.0 pts  
**Function to implement:** `csv_parse_quoted_line`

## Statement

Implement a one-line CSV parser that supports quoted fields, commas inside quotes and escaped quotes represented by doubled quote characters. Reject malformed quoting and capacity overflow.

## Required prototype

```c
int csv_parse_quoted_line(const char *line, CsvField *fields, size_t capacity, size_t *field_count);
```

## Suggested solution steps

1. Use states: FIELD_START, UNQUOTED, QUOTED and AFTER_QUOTE.
2. A comma ends a field only outside quotes.
3. Inside a quoted field, two consecutive quotes produce one literal quote.
4. After a closing quote, accept only comma, line ending or end-of-string.
5. Always terminate each field and report field_count.

## Useful predefined functions / library API

manual state machine, strlen, size_t bounds

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Empty field; empty quoted field; quote in unquoted field; characters after closing quote; unclosed quote; field too long.

## Expected result for the supplied fixture

Three fields; second is Doe, Jane; third is He said "hello".

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
