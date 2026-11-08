# SQL / SQLite (2 pts)

SQL is a **query language**, not a general-purpose structured-data serialization format like JSON or CSV. This exercise uses SQLite as a database file (`school.db`) and SQL statements.

Before running the exercise, create the database from the supplied script:

```sh
sqlite3 school.db < school.sql
```

Implement:
- `sql_count_students` (0.5 pt).
- `sql_add_student` (0.5 pt).
- `sql_update_grade` (0.5 pt).
- `sql_delete_student` (0.5 pt).

Use prepared statements and bind parameters. Do not build SQL queries by concatenating user-provided strings.
