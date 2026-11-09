# JSON proficiencies — practice ideas

These are practice prompts, not claims about the exact forgotten exam question. Use the supplied YAJL exercise directories for the first five.

## Basic — tree API

1. Check whether a JSON file is syntactically valid.
2. Read `name`, `age` and `active` from a root object into a C struct.
3. Read nested `person.address.city` using `yajl_tree_get`.
4. Retrieve an array and count its elements.
5. Loop through a `students` array and print each name.
6. Find a student by integer ID.
7. Calculate average grades from an array of objects.
8. Count objects whose `active` field is JSON true.
9. Validate that a required key exists and has the expected type.
10. Detect absent key, JSON null, wrong type, empty array and malformed JSON.

## Intermediate — nested data and file work

11. Extract a `course` object with a `teacher` object and a `students` array into C structs.
12. Compute the total price of every product in `orders[*].items[*]`.
13. Find all books written by an author ID in a JSON catalogue.
14. Find the most expensive product in an array.
15. Count records by a `status` field (`todo`, `doing`, `done`).
16. Read a config file; use defaults only for optional keys, but fail for required missing keys.
17. Validate a list: every item must contain an integer ID and string label.
18. Convert a JSON array to a C array allocated with `malloc`; keep its length.

## Streaming callbacks

19. Count all strings, integers, arrays and objects in a JSON document.
20. Print every object key using `yajl_map_key`.
21. Sum every integer encountered by `yajl_integer`.
22. Count only the occurrences of a selected key; keep the current key in the callback context.
23. Stop parsing when a callback finds a forbidden value by returning 0.
24. Parse a large JSON file by chunks with repeated `yajl_parse` calls.

## Generator / serialization

25. Create a JSON object from a C struct.
26. Create a JSON array of authors from an array of C structs.
27. Convert a CSV list of books to a JSON array.
28. Export only students with grade >= 10 to a new JSON file.
29. Update one field: parse input tree → copy desired data into C structs → generate a new JSON document. Do not assume YAJL exposes cJSON-like mutation helpers.
30. Write a summary object with `count`, `average` and `passed` values.

## Common exam combinations

- Read JSON → extract array → loop → fill `struct` → print one selected record.
- Read JSON → validate key/type → return `-1` if malformed.
- Read JSON → calculate statistics → print/return result.
- Read JSON → filter records → generate a new JSON file.
- Parse callback events → update context counters → return final totals.

For every prompt, include cleanup and test missing files, invalid JSON, missing members, wrong JSON types, null values, empty arrays and buffers that are too small.
