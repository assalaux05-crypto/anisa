# Exercise 15 — Count JSON nodes recursively

**Difficulty:** Level 3 — Difficult  
**Points:** 3.5 pts  
**Function to implement:** `json_count_nodes`

## Statement

Traverse the whole JSON tree recursively and count objects, arrays and maximum nesting depth. Root depth is 0.

## Required prototype

```c
int json_count_nodes(const char *path, JsonStats *stats);
```

## Suggested solution steps

1. Parse root.
2. Write a recursive helper that receives a JSON value and current depth.
3. If object, increment object count and visit each member value.
4. If array, increment array count and visit each element.
5. Update maximum depth and stop safely on invalid/null pointers.

## Useful predefined functions / library API

object iteration (macro/iterator); array size/get; type predicates; recursion.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Scalar root; empty containers; deeply nested document; null values; count overflow.

## Expected result for the supplied fixture

3 objects, 1 array; maximum depth 2.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
