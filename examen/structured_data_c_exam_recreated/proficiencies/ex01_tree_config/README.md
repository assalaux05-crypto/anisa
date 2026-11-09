# JSON Exercise 1 — read nested configuration with YAJL tree API — 10 points

Use `<yajl/yajl_tree.h>`. Implement `json_read_config`: read `config.json`, parse it with `yajl_tree_parse`, retrieve nested values using `yajl_tree_get`, validate types, and fill the C struct.

```c
typedef struct { char host[64]; int port; int debug; } ServerConfig;
int json_read_config(const char *path, ServerConfig *out);
```

JSON path examples: `{"server", "host", NULL}` and `{"server", "port", NULL}`. Check `YAJL_IS_STRING` / `YAJL_IS_INTEGER` before accessing values. `port` must be 1–65535. `debug` is a JSON boolean (`YAJL_IS_TRUE` / `YAJL_IS_FALSE`). Return `0` on success and `-1` on any file/parse/type/range error. Free the input buffer and parsed tree.

Expected: `localhost`, `8080`, `debug=1`.
