# Exercise 11 — Modify a nested boolean and save JSON

**Difficulty:** Level 3 — Difficult  
**Points:** 3.0 pts  
**Function to implement:** `json_set_user_active`

## Statement

Find a user by id, change its active field to the requested boolean and serialize the complete JSON document to output.

## Required prototype

```c
int json_set_user_active(const char *input, const char *output, int id, int active);
```

## Suggested solution steps

1. Parse the input JSON into a mutable tree.
2. Find users array and matching user object.
3. Replace/set active using a boolean constructor or setter from the library.
4. Serialize root to output, checking write errors.
5. Release both serialized buffer (according to library rules) and root.

## Useful predefined functions / library API

object set/replace; boolean constructor; serialize/print; file output; cleanup.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

ID missing; active other than 0/1; field missing; serialization failure; output equals input.

## Expected result for the supplied fixture

ID 1 active becomes true; other values remain unchanged.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
