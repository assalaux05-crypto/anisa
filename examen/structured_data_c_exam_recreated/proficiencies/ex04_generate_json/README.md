# JSON Exercise 4 — serialize C data with YAJL generator — 10 points

Use `<yajl/yajl_gen.h>`. Implement `json_write_author` and create a JSON object from the C structure. The key and value order should be `id`, `lastname`, `country`.

```c
typedef struct { unsigned id; const char *lastname; const char *country; } Author;
int json_write_author(const char *path, const Author *author);
```

Use `yajl_gen_alloc`, `yajl_gen_config(..., yajl_gen_beautify, 1)`, map open/close, string/integer generation, `yajl_gen_get_buf`, `fwrite`, and `yajl_gen_free`. Check generator statuses and file operations. Never free the borrowed output buffer.

Expected output is valid JSON equivalent to:
```json
{"id":7,"lastname":"Herbert","country":"USA"}
```
