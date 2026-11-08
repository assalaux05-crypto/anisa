# CSV library — proficiency (3 pts)

Use the `libcsv` library rather than splitting lines manually.
- Count valid student records, excluding the header (0.75 pt).
- Find a student by id (0.75 pt).
- Compute the average grade (0.5 pt).
- Export only students with grade >= `minimum` (1 pt).

The fixture deliberately contains a comma inside a quoted field and an escaped quote. A parser based on `strtok(line, ",")` is not sufficient.
