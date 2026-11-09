# YAJL worked patterns

These short examples are the patterns to reproduce in a TP. They are not complete project solutions; add argument checking and file error handling in your function.

## A. Read a JSON file, parse it as a tree, retrieve a key

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yajl/yajl_tree.h>

static char *read_all(const char *path)
{
    FILE *file = fopen(path, "rb");
    long size;
    char *buffer;
    if (!file) return NULL;
    if (fseek(file, 0, SEEK_END) != 0) { fclose(file); return NULL; }
    size = ftell(file);
    if (size < 0 || fseek(file, 0, SEEK_SET) != 0) { fclose(file); return NULL; }
    buffer = malloc((size_t)size + 1);
    if (!buffer) { fclose(file); return NULL; }
    if (fread(buffer, 1, (size_t)size, file) != (size_t)size) {
        free(buffer); fclose(file); return NULL;
    }
    buffer[size] = '\0';
    fclose(file);
    return buffer;
}

int print_person_name(const char *path)
{
    char *text = read_all(path);
    char error[256] = {0};
    yajl_val root;
    const char *name_path[] = {"person", "name", NULL};
    yajl_val name;
    if (!text) return -1;
    root = yajl_tree_parse(text, error, sizeof(error));
    free(text);
    if (!root) {
        fprintf(stderr, "Invalid JSON: %s\n", error);
        return -1;
    }
    name = yajl_tree_get(root, name_path, yajl_t_string);
    if (!name) { yajl_tree_free(root); return -1; }
    printf("name: %s\n", YAJL_GET_STRING(name));
    yajl_tree_free(root);
    return 0;
}
```

## B. JSON object → C struct

Example JSON:

```json
{
  "author": { "id": 7, "lastname": "Herbert" }
}
```

C structure:

```c
typedef struct {
    unsigned id;
    char lastname[64];
} Author;
```

Extraction pattern:

```c
const char *id_path[] = {"author", "id", NULL};
const char *last_path[] = {"author", "lastname", NULL};
yajl_val id = yajl_tree_get(root, id_path, yajl_t_number);
yajl_val last = yajl_tree_get(root, last_path, yajl_t_string);
if (!id || !last || !YAJL_IS_INTEGER(id) || !YAJL_IS_STRING(last))
    return -1;
if (strlen(YAJL_GET_STRING(last)) >= sizeof(author.lastname))
    return -1;
author.id = (unsigned)YAJL_GET_INTEGER(id);
strcpy(author.lastname, YAJL_GET_STRING(last));
```

## C. Loop through an array

JSON:

```json
{"students":[{"id":1,"name":"Amina"},{"id":2,"name":"Yacine"}]}
```

Pattern:

```c
const char *students_path[] = {"students", NULL};
yajl_val students = yajl_tree_get(root, students_path, yajl_t_array);
if (!students) return -1;
for (size_t i = 0; i < YAJL_GET_ARRAY(students)->len; i++) {
    yajl_val item = YAJL_GET_ARRAY(students)->values[i];
    const char *id_path[] = {"id", NULL};
    const char *name_path[] = {"name", NULL};
    yajl_val id = yajl_tree_get(item, id_path, yajl_t_number);
    yajl_val name = yajl_tree_get(item, name_path, yajl_t_string);
    if (!id || !name) return -1;
    printf("%lld %s\n", YAJL_GET_INTEGER(id), YAJL_GET_STRING(name));
}
```

Notice the two lookup levels: `students` is obtained from the root; then `id` and `name` are read from each array item.

## D. Streaming parse — callback state

```c
#include <stdio.h>
#include <string.h>
#include <yajl/yajl_parse.h>

typedef struct {
    size_t strings;
    size_t integers;
    size_t objects;
    size_t arrays;
    char last_key[64];
} Stats;

static int on_string(void *ctx, const unsigned char *value, size_t len)
{
    Stats *stats = ctx;
    (void)value;
    (void)len;
    stats->strings++;
    return 1; /* non-zero = continue parsing */
}

static int on_integer(void *ctx, long long value)
{
    Stats *stats = ctx;
    (void)value;
    stats->integers++;
    return 1;
}

static int on_key(void *ctx, const unsigned char *key, size_t len)
{
    Stats *stats = ctx;
    size_t copy = len < sizeof(stats->last_key) - 1 ? len : sizeof(stats->last_key) - 1;
    memcpy(stats->last_key, key, copy);
    stats->last_key[copy] = '\0';
    return 1;
}

static int on_map_start(void *ctx)
{
    ((Stats *)ctx)->objects++;
    return 1;
}

static int on_array_start(void *ctx)
{
    ((Stats *)ctx)->arrays++;
    return 1;
}

static const yajl_callbacks callbacks = {
    .yajl_integer = on_integer,
    .yajl_string = on_string,
    .yajl_map_key = on_key,
    .yajl_start_map = on_map_start,
    .yajl_start_array = on_array_start
};
```

The rest of the parser setup:

```c
Stats stats = {0};
yajl_handle handle = yajl_alloc(&callbacks, NULL, &stats);
if (!handle) return -1;
yajl_status status = yajl_parse(handle,
    (const unsigned char *)json_text, strlen(json_text));
if (status == yajl_status_ok)
    status = yajl_complete_parse(handle);
if (status != yajl_status_ok) {
    unsigned char *error = yajl_get_error(handle, 1,
        (const unsigned char *)json_text, strlen(json_text));
    if (error) {
        fprintf(stderr, "%s\n", error);
        yajl_free_error(handle, error);
    }
    yajl_free(handle);
    return -1;
}
printf("strings=%zu integers=%zu objects=%zu arrays=%zu\n",
       stats.strings, stats.integers, stats.objects, stats.arrays);
yajl_free(handle);
```

For a large file, read it in chunks and call `yajl_parse` for each chunk. After the last chunk, call `yajl_complete_parse`.

## E. Generate JSON from C values

```c
#include <stdio.h>
#include <string.h>
#include <yajl/yajl_gen.h>

int write_one_author(const char *path, unsigned id, const char *lastname)
{
    FILE *file = NULL;
    yajl_gen gen = yajl_gen_alloc(NULL);
    const unsigned char *buffer = NULL;
    size_t length = 0;
    yajl_gen_status status;
    if (!gen) return -1;
    (void)yajl_gen_config(gen, yajl_gen_beautify, 1);

    status = yajl_gen_map_open(gen);
    if (status == yajl_gen_status_ok)
        status = yajl_gen_string(gen, (const unsigned char *)"id", 2);
    if (status == yajl_gen_status_ok)
        status = yajl_gen_integer(gen, id);
    if (status == yajl_gen_status_ok)
        status = yajl_gen_string(gen, (const unsigned char *)"lastname", 8);
    if (status == yajl_gen_status_ok)
        status = yajl_gen_string(gen, (const unsigned char *)lastname, strlen(lastname));
    if (status == yajl_gen_status_ok)
        status = yajl_gen_map_close(gen);
    if (status != yajl_gen_status_ok) { yajl_gen_free(gen); return -1; }

    status = yajl_gen_get_buf(gen, &buffer, &length);
    if (status != yajl_gen_status_ok) { yajl_gen_free(gen); return -1; }
    file = fopen(path, "wb");
    if (!file) { yajl_gen_free(gen); return -1; }
    if (fwrite(buffer, 1, length, file) != length) {
        fclose(file); yajl_gen_free(gen); return -1;
    }
    if (fclose(file) != 0) { yajl_gen_free(gen); return -1; }
    yajl_gen_free(gen);
    return 0;
}
```

To generate arrays, use `yajl_gen_array_open` / `yajl_gen_array_close`. Every object key must be emitted as a string. Generator output is already escaped correctly; do not manually add JSON quotes around it.

## F. Safe cleanup checklist

- File buffer allocated by your program → `free(buffer)`.
- Parsed tree from `yajl_tree_parse` → `yajl_tree_free(root)`.
- Parser handle from `yajl_alloc` → `yajl_free(handle)`.
- Error string from `yajl_get_error` → `yajl_free_error(handle, error)` before freeing the handle.
- Generator handle from `yajl_gen_alloc` → `yajl_gen_free(gen)`.
- The pointer from `yajl_gen_get_buf` is borrowed from the generator; do not free it.
