# Exercise 01 — Parse JSON and count an array

**Difficulty:** Level 1 — Easy  
**Points:** 1.0 pts  
**Function to implement:** `json_count_courses`

## Statement

Use the library supplied in the TP to parse the file and count elements in the root courses array. Return 1 on success, 0 on parse/type/file error.

## Required prototype

```c
int json_count_courses(const char *path, size_t *count);
```

## Suggested solution steps

1. Parse the complete file into the library JSON root value.
2. Check that the root is an object.
3. Get courses and check that it is an array.
4. Count its elements and release the root value using the library cleanup function.

## Useful predefined functions / library API

Library parse-file/parse-string function; object-get; is-array/type check; array-size; root cleanup.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Missing file; malformed JSON; missing courses key; courses is null/string/object.

## Expected result for the supplied fixture

Count is 3.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
