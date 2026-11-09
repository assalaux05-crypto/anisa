# Exercise 09 — Validate required fields and exact JSON types

**Difficulty:** Level 3 — Difficult  
**Points:** 3.0 pts  
**Function to implement:** `json_validate_products`

## Statement

Validate every product. Required keys: id (integer), name (string), price (number >= 0), stock (integer >= 0). Return 1 if all are valid; otherwise return 0, set bad_index to the zero-based product index and write a short reason.

## Required prototype

```c
int json_validate_products(const char *path, size_t *bad_index, char *message, size_t message_size);
```

## Suggested solution steps

1. Parse root and verify products array.
2. For every element, verify object type.
3. Check each required key exists and has the exact type.
4. Check numeric constraints.
5. Stop on first error and fill message safely.

## Useful predefined functions / library API

object_get; type predicates; number/integer getters; snprintf.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Missing key; null; boolean instead of number; negative price; negative stock; wrong root shape.

## Expected result for the supplied fixture

Fails at index 1 because price is a string.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
