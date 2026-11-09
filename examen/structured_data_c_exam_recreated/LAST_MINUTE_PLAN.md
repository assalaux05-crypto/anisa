# Last-minute plan — focused practice

## Priority 1 — CSV (first half of revision)

1. Read `fundamentals/ex01_unsigned/README.md`; implement the one-line conversion.
2. Do `ex02_parse_field` without `strtok`: understand `char **input`, pointer movement, commas and empty fields.
3. Do `ex03_authors_books`: first parse one author row into a struct, then find the author ID, then scan books and print matching titles.
4. Rebuild all three with `make` and run their mains.
5. Read `solutions/CSV_SOLUTIONS.md` only after attempting each one.

## Priority 2 — YAJL tree API

Learn this sequence:

```text
read JSON file into a NUL-terminated buffer
        ↓
yajl_tree_parse(buffer, error_buffer, error_size)
        ↓
check returned yajl_val root
        ↓
yajl_tree_get(root, path, expected_type)
        ↓
YAJL_IS_* / YAJL_GET_* checks and extraction
        ↓
yajl_tree_free(root) + free(file buffer)
```

The tree API is the easiest route for an exam question asking you to retrieve fields from a JSON object or array and put them into a C struct.

## Priority 3 — callbacks

Memorize the callback table names: `yajl_null`, `yajl_boolean`, `yajl_integer`, `yajl_double`, `yajl_number`, `yajl_string`, `yajl_start_map`, `yajl_map_key`, `yajl_end_map`, `yajl_start_array`, `yajl_end_array`.

A callback returns non-zero to continue. Use `ctx` to carry your counters/struct. For `yajl_string` and `yajl_map_key`, copy exactly `len` bytes if you need a C string.

## Priority 4 — generator / serialization

Remember the structure-building order:

```c
yajl_gen_map_open(g);
yajl_gen_string(g, (const unsigned char *)"name", 4); // key
yajl_gen_string(g, (const unsigned char *)"Amina", 5); // value
yajl_gen_map_close(g);
yajl_gen_get_buf(g, &buf, &len);
fwrite(buf, 1, len, file);
yajl_gen_free(g);
```

Check each generator status. A map key must be generated with `yajl_gen_string`.

## Essential checks

- `yajl_tree_parse` returns NULL for invalid JSON.
- A missing key makes `yajl_tree_get` return NULL.
- Always check `YAJL_IS_STRING`, `YAJL_IS_INTEGER`, `YAJL_IS_ARRAY`, etc. before reading union data.
- `YAJL_GET_INTEGER` returns `long long`, not `int`.
- Arrays are accessed with `YAJL_GET_ARRAY(arr)->values[i]`; `yajl_tree_get` paths traverse object keys, not array indexes.
- Tree string values are owned by the tree; do not free them individually. Free the whole tree once with `yajl_tree_free`.
- Never `free()` a YAJL generator buffer. It belongs to the generator; write it before `yajl_gen_free`.
- After feeding all input chunks, call `yajl_complete_parse`.
