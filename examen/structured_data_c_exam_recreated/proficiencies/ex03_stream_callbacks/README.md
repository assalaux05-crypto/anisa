# JSON Exercise 3 — YAJL streaming callbacks — 10 points

Use `<yajl/yajl_parse.h>`. Parse `stats.json` using callback functions. Count strings, integers, arrays and objects. Store counters in the context struct passed to `yajl_alloc`.

```c
typedef struct { size_t strings, integers, arrays, objects; } JsonStats;
int json_count_events(const char *path, JsonStats *out);
```

Callback names: `yajl_string`, `yajl_integer`, `yajl_start_array`, `yajl_start_map`. Every callback returns `1` to continue. Read the file, feed its bytes to `yajl_parse`, call `yajl_complete_parse`, inspect status, then `yajl_free`.

Important: the string callback receives `(const unsigned char *value, size_t len)`, not a guaranteed NUL-terminated string. You only need the length here, so do not call `strlen` on it.
