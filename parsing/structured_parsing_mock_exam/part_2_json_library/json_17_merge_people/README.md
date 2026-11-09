# Exercise 17 — Merge two JSON user arrays without duplicate IDs

**Difficulty:** Level 4 — Expert  
**Points:** 4.0 pts  
**Function to implement:** `json_merge_people`

## Statement

Create one output document. Copy all users from left, then users from right whose id has not appeared before. Keep the left version when an ID is repeated.

## Required prototype

```c
int json_merge_people(const char *left, const char *right, const char *output);
```

## Suggested solution steps

1. Parse both files and validate the root/users arrays.
2. Create a new output root and users array.
3. Append deep copies of left users.
4. For each right user, search IDs already copied; append only unseen IDs.
5. Serialize once and release all three trees.

## Useful predefined functions / library API

parse; create object/array; deep copy; append; object get; serialize; cleanup.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Missing arrays; duplicate IDs inside one input; malformed second file; empty arrays; allocation failure.

## Expected result for the supplied fixture

Output contains IDs 1, 2, 3; ID 2 uses Bob from left.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
