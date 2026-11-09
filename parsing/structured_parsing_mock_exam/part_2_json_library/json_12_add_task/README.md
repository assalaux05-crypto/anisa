# Exercise 12 — Append a new object to a JSON array

**Difficulty:** Level 3 — Difficult  
**Points:** 3.0 pts  
**Function to implement:** `json_add_task`

## Statement

Create a JSON object from JsonTask, append it to tasks, and write the complete document. Do not manually concatenate JSON strings.

## Required prototype

```c
int json_add_task(const char *input, const char *output, const JsonTask *task);
```

## Suggested solution steps

1. Parse root and validate tasks array.
2. Create a new JSON object.
3. Create/add id, title and done members using library constructors.
4. Append the object to the array (check ownership-transfer rules for the selected library).
5. Serialize and clean up correctly.

## Useful predefined functions / library API

new object; add/set member; new number/string/bool; array append; serialize; cleanup.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

tasks missing/wrong type; allocation failure; title contains quotes/newline; duplicate id policy (reject).

## Expected result for the supplied fixture

Two tasks in output.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
