# Exercise 08 — Average grades inside a nested course

**Difficulty:** Level 2 — Medium  
**Points:** 2.5 pts  
**Function to implement:** `json_average_course_grade`

## Statement

Find the course, iterate over its students array, and calculate the average grade.

## Required prototype

```c
int json_average_course_grade(const char *path, int course_id, double *average, size_t *count);
```

## Suggested solution steps

1. Find the course object by id.
2. Check students is an array.
3. Validate each student object and numeric grade.
4. Accumulate sum/count and reject a course with no valid grades.

## Useful predefined functions / library API

object_get, array_size/get, is_number, number_value.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Course missing; empty students; one malformed student; numeric real values; wrong type.

## Expected result for the supplied fixture

Course 2 average is 14.00 across 3 students.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
