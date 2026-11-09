# Exercise 02 — Read a string field safely

**Difficulty:** Level 1 — Easy  
**Points:** 1.5 pts  
**Function to implement:** `json_get_app_name`

## Statement

Extract app.name into out. Check every parent and field type before reading its value. Return 0 if missing, wrong type or output buffer too small.

## Required prototype

```c
int json_get_app_name(const char *path, char *out, size_t out_size);
```

## Suggested solution steps

1. Parse root; get app object.
2. Get name from app and verify it is a JSON string.
3. Read the library-owned string and copy it using snprintf or an explicit length check.
4. Free the JSON root after copying; do not return a pointer into the freed tree.

## Useful predefined functions / library API

object_get, is_string/type check, string_value, snprintf/strlcpy equivalent, root_free.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Missing app; app is an array; name is null/number; long name; empty string.

## Expected result for the supplied fixture

Dahoun Store.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
