# Exercise 03 — Extract a field from a simple CSV line

**Difficulty:** Level 1 — Easy  
**Points:** 1.5 pts  
**Function to implement:** `csv_get_field`

## Statement

Copy the field at zero-based index into out and terminate it with \0. Return 1 on success and 0 for invalid arguments, missing field or insufficient output capacity. This level assumes no quotes.

## Required prototype

```c
int csv_get_field(const char *line, size_t index, char *out, size_t out_size);
```

## Suggested solution steps

1. Validate line, out and out_size.
2. Walk through characters and count commas until the requested field starts.
3. Copy until the next comma or line ending; do not overflow out.
4. Write the null terminator and return success.

## Useful predefined functions / library API

strlen, strchr, memcpy or a character loop

**Important:** CSV parsing in Part I must be implemented manually. Do not use libcsv or another CSV parser. The C standard library functions listed above are allowed helpers, not CSV parsing libraries.

## Cases you must test

Index 0; last field; empty field; index out of range; buffer too small.

## Expected result for the supplied fixture

Index 1 gives Manel.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
