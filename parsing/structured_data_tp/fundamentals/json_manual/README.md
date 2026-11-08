# JSON — manual parsing (3 pts)

Implement a small parser for **this fixture's restricted JSON subset**:
- top-level string and non-negative integer values;
- a top-level array named `students` containing simple objects;
- whitespace may appear between tokens.

Tasks:
- `json_get_string` (0.75 pt).
- `json_get_int` (0.5 pt).
- `json_count_students` (1 pt).
- `json_update_semester` (0.75 pt).

This is not a complete JSON parser. You must detect missing keys, wrong value types, missing files and malformed delimiters. A fully correct JSON parser must also handle escaped strings, Unicode, negative/floating/scientific numbers, nesting and more; that is why real projects use a library.
