# CSV — manual parsing (3.5 pts)

Implement the functions in `exercise.h` using `fopen`, `fgets`, `fprintf`, `fclose`, and other standard C functions.

- `csv_count_rows`: count records, excluding the header (0.5 pt).
- `csv_find_student`: find an id and copy its name safely (1 pt).
- `csv_add_student`: append a new record (0.5 pt).
- `csv_update_grade`: update one record while preserving the other records (1 pt).
- `csv_delete_student`: remove one record (0.5 pt).

For update/delete, use a temporary file if necessary. Do not assume that every line fits in a tiny buffer. This basic exercise uses simple unquoted fields; quoted CSV parsing is tested in Proficiencies.
