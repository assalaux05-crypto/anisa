# Exercise 18 — Round-trip JSON through C structures

**Difficulty:** Level 4 — Expert  
**Points:** 4.0 pts  
**Function to implement:** `json_roundtrip_courses`

## Statement

Parse courses into an allocated array of C structs, then create a fresh JSON document from those structs and write it. This is a deliberate JSON → struct → JSON round trip.

## Required prototype

```c
int json_roundtrip_courses(const char *input, const char *output);
```

## Suggested solution steps

1. Parse and validate the input.
2. Allocate a C array sized to the JSON array.
3. Copy and validate each object into a struct.
4. Create a new JSON root/array and recreate every field from the structs.
5. Serialize, then free the C array and both JSON trees.

## Useful predefined functions / library API

malloc/calloc; type checks; constructors; object add; array append; serialize; cleanup.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Empty array; missing field; allocation failure; escaped title; booleans; output must remain valid JSON.

## Expected result for the supplied fixture

Output has the same two course objects and valid escaping.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
