# Exercise 2 — parse the field before the comma — 10 points

**Prototype (keep exactly):**
```c
char *parse_field(char **input);
```

`input` points to a cursor inside a writable CSV line. Return a pointer to the current field, replace the next comma (or line ending) with `\0`, and advance `*input` to the character after the comma. When there is no comma, set `*input = NULL` after returning the final field. Preserve empty fields, including an empty field after a trailing comma.

The returned field is a **borrowed pointer into the original line**. Do not `free` it. The caller must keep the line buffer alive while using the field. If the value must outlive the row, duplicate it.

This exercise uses the simple CSV subset in `fields.csv`: no quoted fields and no commas inside values. Return NULL for a NULL `input` or NULL `*input`.

Example:
```c
char row[] = "18,manel,alger";
char *cursor = row;
char *a = parse_field(&cursor); /* "18"; cursor now at "manel,alger" */
char *b = parse_field(&cursor); /* "manel"; cursor now at "alger" */
char *c = parse_field(&cursor); /* "alger"; cursor now NULL */
/* a, b and c point inside row; do not free them. */
```

Build: `make && ./test`
