# JSON Exercise 2 — nested array → C structs — 10 points

Parse `students.json`. The root has a `class` object; it contains `name` and a `students` array. Convert every student object to a C `Student` entry. Do not assume `yajl_tree_get` can index arrays: get the array node, then use `YAJL_GET_ARRAY(array)->values[i]`.

```c
typedef struct { int id; char name[64]; int grade; } Student;
int json_read_students(const char *path, Student *out, size_t capacity,
                       size_t *count);
```

Return `-1` if the array is absent, an item is not an object, a required field is missing/wrong type, the array exceeds capacity, or the file/JSON is invalid. Set `*count` only after successful parsing. Validate grade in 0–20 and ensure name fits. Tree strings belong to the tree; copy them into your struct before calling `yajl_tree_free`.

Expected student count: 3. Expected names: Amina, Yacine, Imane.
