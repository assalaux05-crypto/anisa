# Exercise 13 — Delete an object from a JSON array by ID

**Difficulty:** Level 3 — Difficult  
**Points:** 3.0 pts  
**Function to implement:** `json_delete_product`

## Statement

Remove the first object with matching id from products and serialize the document. Return 0 if not found.

## Required prototype

```c
int json_delete_product(const char *input, const char *output, int id);
```

## Suggested solution steps

1. Parse root and validate products array.
2. Loop over array elements and find matching id.
3. Use the library array-removal function (or build a new array if that library lacks one).
4. Serialize after removal and clean up.

## Useful predefined functions / library API

array size/get; object get; detach/delete/remove array item; serialize; cleanup.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

First/last element; empty array; ID missing; duplicate IDs; array not mutable.

## Expected result for the supplied fixture

ID 2 is removed; IDs 1 and 3 remain.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
