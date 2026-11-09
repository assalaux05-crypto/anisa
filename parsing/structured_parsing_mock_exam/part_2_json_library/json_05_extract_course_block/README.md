# Exercise 05 — Extract a complete nested JSON block into structs

**Difficulty:** Level 2 — Medium  
**Points:** 3.0 pts  
**Function to implement:** `json_extract_course_block`

## Statement

Find a course object and map its nested teacher object and students array directly into the provided JsonCourse struct. Respect the fixed array capacity JSON_MAX_STUDENTS.

## Required prototype

```c
int json_extract_course_block(const char *path, int wanted_id, JsonCourse *out);
```

## Suggested solution steps

1. Parse the JSON file and get the root courses array.
2. Find the course object whose id equals wanted_id.
3. Read scalar fields from that object into JsonCourse.
4. Get teacher as an object, then copy teacher.name and teacher.room.
5. Get students as an array; for each object, fill one JsonStudent entry after checking capacity and field types.
6. Set student_count and free the JSON tree.

## Useful predefined functions / library API

object_get, array_get/iteration, type predicates, value accessors, snprintf, free root.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

No matching course; teacher missing; students not array; array larger than capacity; one student with wrong grade type; long title.

## Expected result for the supplied fixture

Course 10 has title C Programming, teacher Dr. Ali, and 2 students.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
