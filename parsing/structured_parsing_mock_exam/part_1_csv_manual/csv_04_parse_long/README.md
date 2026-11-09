# Exercise 04 — Convert a field into an integer safely

**Difficulty:** Level 1 — Easy  
**Points:** 1.5 pts  
**Function to implement:** `csv_parse_long`

## Statement

Parse one complete base-10 integer. Accept surrounding whitespace; reject empty strings, trailing junk and overflow. Do not use atoi.

## Required prototype

```c
int csv_parse_long(const char *text, long *value);
```

## Suggested solution steps

1. Skip leading whitespace with isspace.
2. Call strtol(text, &end, 10) after setting errno = 0.
3. Reject when no digits were consumed, errno is ERANGE, or non-whitespace remains.
4. Store the result only after all checks pass.

## Useful predefined functions / library API

strtol, errno, ERANGE, isspace, limits.h

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

0; negative values; + sign; spaces; "12x"; empty string; overflow.

## Expected result for the supplied fixture

" -42 " succeeds with -42; "12x" fails.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
