# Exercise 10 — Sum valid values in a mixed-type array

**Difficulty:** Level 3 — Difficult  
**Points:** 3.0 pts  
**Function to implement:** `json_sum_valid_scores`

## Statement

Sum only JSON numbers. Ignore null, strings and booleans; report how many numeric values were used.

## Required prototype

```c
int json_sum_valid_scores(const char *path, double *sum, size_t *used);
```

## Suggested solution steps

1. Parse root; validate scores is an array.
2. Loop over each element.
3. Use the library type predicate to accept only numeric values.
4. Accumulate as double and increment used.

## Useful predefined functions / library API

array_size/get; type predicates; number getter.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

All invalid values; empty array; integer and real; booleans must not be treated as numbers in libraries that expose booleans separately.

## Expected result for the supplied fixture

Sum 30.5 using 3 values.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
