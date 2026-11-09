# Exercise 07 — Handle missing, null and optional JSON values

**Difficulty:** Level 2 — Medium  
**Points:** 2.5 pts  
**Function to implement:** `json_read_settings`

## Statement

Extract theme, fontSize and notifications. Defaults: theme="light", fontSize=14, notifications=1. Missing optional fields use defaults. A present field of the wrong type is an error; JSON null means notifications remains at its default.

## Required prototype

```c
int json_read_settings(const char *path, JsonSettings *out);
```

## Suggested solution steps

1. Initialize the output with the documented defaults first.
2. Parse root and get settings object.
3. For each optional key, distinguish missing from present.
4. If present and not null, verify exact type and overwrite the default.
5. Release root and return status.

## Useful predefined functions / library API

object_get; key-existence or null/type predicates; string/number/bool getters.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Whole settings missing; explicit null; false boolean; fontSize 0; wrong type; unknown extra fields.

## Expected result for the supplied fixture

Theme dark, font size 16, notifications default 1.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
