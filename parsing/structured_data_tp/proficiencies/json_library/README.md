# JSON library — proficiency (3.5 pts)

Use `cJSON` to parse, inspect, modify and serialize the document.
- Count course objects (0.5 pt).
- Count all students in all courses (1 pt).
- Update the room for the matching course id and rewrite the JSON file (1 pt).
- Export students whose grade >= `minimum` to a new JSON array (1 pt).

Check the type of every value before using it. Handle parse failures and missing keys. Free the cJSON tree and printed buffers correctly. Do not parse JSON with `strstr` or manual brace counting in this exercise.
