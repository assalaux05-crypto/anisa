# Exercise 06 — Convert a JSON array into a dynamically allocated struct array

**Difficulty:** Level 2 — Medium  
**Points:** 3.0 pts  
**Function to implement:** `json_load_users`

## Statement

Allocate exactly enough JsonUser elements, fill them from users[], and return the array/count. The caller owns the returned array and must free(*users). On any failure, free partial allocations and set *users = NULL and *count = 0.

## Required prototype

```c
int json_load_users(const char *path, JsonUser **users, size_t *count);
```

## Suggested solution steps

1. Initialize output parameters before parsing.
2. Validate root and users array.
3. Allocate array_length * sizeof(JsonUser), checking malloc.
4. Convert every object with strict type checks and bounded string copies.
5. On failure, free the allocated array and JSON root; on success, free only the JSON root and return the C array.

## Useful predefined functions / library API

malloc/calloc, sizeof, array_size/get, type checks, snprintf, free.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Empty array; allocation failure; malformed element halfway through; long name; outputs initially non-zero.

## Expected result for the supplied fixture

Returns 3 structs; caller calls free(users).

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
