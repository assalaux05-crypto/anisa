# Exercise 19 — Validate a nested order and report the exact error path

**Difficulty:** Level 4 — Expert  
**Points:** 4.0 pts  
**Function to implement:** `json_validate_order`

## Statement

Validate: order object; id integer; customer.name string; items non-empty array; each item has integer product_id > 0 and quantity integer > 0. Return 1 if valid. Otherwise return 0 and write the first failing JSON-like path, e.g. items[1].quantity.

## Required prototype

```c
int json_validate_order(const char *path, char *error_path, size_t error_size);
```

## Suggested solution steps

1. Validate one level at a time, checking type before reading a value.
2. Build an error path for the first failure with snprintf.
3. Use a loop over the items array and include the element index.
4. Stop at first error and clean up the JSON root.

## Useful predefined functions / library API

object_get; type checks; array size/get; snprintf.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Missing order; customer null; items empty; product_id 0; quantity negative/string; output path buffer too small.

## Expected result for the supplied fixture

Fails at items[1].quantity.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
