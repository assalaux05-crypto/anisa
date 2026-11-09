# Exercise 04 — Find a user and extract a C struct

**Difficulty:** Level 2 — Medium  
**Points:** 2.0 pts  
**Function to implement:** `json_find_user`

## Statement

Find one user by id and copy id, name and active into JsonUser. Do not store pointers to library-owned strings in the struct.

## Required prototype

```c
int json_find_user(const char *path, int wanted_id, JsonUser *out);
```

## Suggested solution steps

1. Parse the root and get the users array.
2. For each array element, check that it is an object.
3. Read id as integer, name as string and active as boolean using type checks.
4. When the id matches, copy into a temporary JsonUser and assign it to *out.
5. Release the JSON root.

## Useful predefined functions / library API

array iteration; object get; is_integer/is_number; is_string; is_boolean; snprintf; cleanup.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

User not found; missing name; id represented as string; active missing/null; duplicate IDs.

## Expected result for the supplied fixture

ID 8 gives Bob and active = 0.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
