# Exercise 16 — Report a JSON parse error

**Difficulty:** Level 3 — Difficult  
**Points:** 2.5 pts  
**Function to implement:** `json_report_parse_error`

## Statement

Attempt to parse the file. If valid, return 1 and write "valid". If invalid, return 0 and copy the parser error description (and line/column if the library provides them) into message.

## Required prototype

```c
int json_report_parse_error(const char *path, char *message, size_t message_size);
```

## Suggested solution steps

1. Read/parse the file using the selected library.
2. Check the parser result before accessing fields.
3. Use the error object or error accessor provided by that library.
4. Format a bounded diagnostic message.
5. Release parser/error resources as required.

## Useful predefined functions / library API

parse error object or error accessor; snprintf; cleanup.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

File missing; empty file; invalid token; trailing comma; output buffer too small.

## Expected result for the supplied fixture

Returns invalid and a non-empty diagnostic.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
