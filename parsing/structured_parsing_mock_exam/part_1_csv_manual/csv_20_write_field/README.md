# Exercise 20 — Write one CSV field with correct escaping

**Difficulty:** Level 4 — Expert  
**Points:** 3.5 pts  
**Function to implement:** `csv_write_field`

## Statement

Write exactly one valid CSV field. Quote the value if it contains comma, double quote, CR or LF. Inside a quoted field, write each double quote twice.

## Required prototype

```c
int csv_write_field(FILE *stream, const char *value);
```

## Suggested solution steps

1. Scan the value to determine whether quoting is needed.
2. If needed, write an opening quote.
3. Write each character; when it is a quote, write it twice.
4. Write the closing quote when needed and check every output operation.

## Useful predefined functions / library API

fputc, ferror, strchr or a loop

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Empty string; quote only; comma; newline; null arguments; write failure.

## Expected result for the supplied fixture

Dora, Jr. becomes quoted; embedded quotes are doubled.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
