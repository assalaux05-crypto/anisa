# Exercise 14 — Filter objects into a new JSON document

**Difficulty:** Level 3 — Difficult  
**Points:** 3.0 pts  
**Function to implement:** `json_export_available_products`

## Statement

Create a new JSON document containing only products with stock > 0. Keep the product objects intact; do not stringify and concatenate them by hand.

## Required prototype

```c
int json_export_available_products(const char *input, const char *output);
```

## Suggested solution steps

1. Parse the input document.
2. Create a new root object and products array.
3. Iterate source products; validate stock as integer.
4. Add a deep copy of matching objects to the new array (or reconstruct them).
5. Serialize the new document and release both trees.

## Useful predefined functions / library API

array iteration; deep-copy or create object; add item; serialize; cleanup.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

No available products; null stock; empty source; wrong stock type.

## Expected result for the supplied fixture

Output contains IDs 1 and 3.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
