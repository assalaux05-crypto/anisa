# Exercise 20 — Migrate an older JSON schema to a new schema

**Difficulty:** Level 4 — Expert  
**Points:** 4.5 pts  
**Function to implement:** `json_migrate_v1_to_v2`

## Statement

Convert version 1 to version 2: rename username to name; convert enabled integer 0/1 to boolean active; add role="user"; keep id; output version=2. Build new JSON objects using the library API.

## Required prototype

```c
int json_migrate_v1_to_v2(const char *input, const char *output);
```

## Suggested solution steps

1. Parse and validate version is integer 1 and users is an array.
2. Create a fresh root with version 2 and a new users array.
3. For each user, validate id/username/enabled.
4. Build a new object containing id, name, active boolean and role string.
5. Serialize and release all resources.

## Useful predefined functions / library API

parse; object/array constructors; add members; boolean constructors; serialize; cleanup.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Unsupported version; enabled is 2; missing username; malformed user halfway through; escaped names.

## Expected result for the supplied fixture

Ada maps to name Ada, active true, role user; Bob active false.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
