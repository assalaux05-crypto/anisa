# YAJL C library — function and concept reference

> This reference targets YAJL 2.x headers (`yajl_parse.h`, `yajl_tree.h`, `yajl_gen.h`). It is not the API for Jansson or cJSON.

## 1. What YAJL does

YAJL = **Yet Another JSON Library**. It is a C library for parsing and generating JSON. Its main design is event-driven: as tokens are parsed, YAJL invokes the callbacks you provide. The optional tree API builds a tree of JSON values for convenient navigation. The generator API writes syntactically valid JSON from typed calls.

| Interface | Header | Mental model | Best use |
|---|---|---|---|
| Streaming parser | `<yajl/yajl_parse.h>` | SAX/events/callbacks | Large files, event counting, sequential processing |
| Tree parser | `<yajl/yajl_tree.h>` | DOM/tree | Retrieve nested keys and arrays, validate fields, map to structs |
| Generator | `<yajl/yajl_gen.h>` | Typed JSON writer | Create JSON or serialize modified C data |
| Shared definitions | `<yajl/yajl_common.h>` | allocator/types | Usually included indirectly |

Install on Debian/Kali with `sudo apt install libyajl-dev`. Link using `-lyajl`.

## 2. Tree API — usually easiest for nested exam data

### Main functions

| Function | Purpose |
|---|---|
| `yajl_tree_parse(input, error_buffer, error_buffer_size)` | Parse a NUL-terminated JSON string into a tree; returns root or `NULL`. |
| `yajl_tree_get(parent, path, type)` | Find a nested object member through a NULL-terminated array of key strings. Returns `NULL` if absent/wrong type. |
| `yajl_tree_free(root)` | Release the whole parsed tree. `NULL` is accepted. |

`yajl_tree_parse` does **not** take a filename. You must read the file into a NUL-terminated memory buffer first.

### JSON types

`yajl_type` values:

- `yajl_t_string`
- `yajl_t_number`
- `yajl_t_object`
- `yajl_t_array`
- `yajl_t_true`
- `yajl_t_false`
- `yajl_t_null`
- `yajl_t_any` (useful as a requested type in `yajl_tree_get`; not an actual node type)

### Type-checking macros

| Macro | Meaning |
|---|---|
| `YAJL_IS_STRING(v)` | non-NULL string node |
| `YAJL_IS_NUMBER(v)` | any number node |
| `YAJL_IS_INTEGER(v)` | number with a valid 64-bit integer representation |
| `YAJL_IS_DOUBLE(v)` | number with a valid double representation |
| `YAJL_IS_OBJECT(v)` | object node |
| `YAJL_IS_ARRAY(v)` | array node |
| `YAJL_IS_TRUE(v)` / `YAJL_IS_FALSE(v)` | boolean true/false |
| `YAJL_IS_NULL(v)` | JSON null |

### Value-access macros

| Macro | Value |
|---|---|
| `YAJL_GET_STRING(v)` | `char *` string, or NULL for a non-string |
| `YAJL_GET_NUMBER(v)` | original number as text; check number type first |
| `YAJL_GET_DOUBLE(v)` | `double`; check `YAJL_IS_DOUBLE` first |
| `YAJL_GET_INTEGER(v)` | `long long`; check `YAJL_IS_INTEGER` first |
| `YAJL_GET_OBJECT(v)` | pointer to object storage, or NULL |
| `YAJL_GET_ARRAY(v)` | pointer to array storage, or NULL |

### Accessing object keys

```c
const char *path[] = {"person", "name", NULL};
yajl_val name = yajl_tree_get(root, path, yajl_t_string);
if (name == NULL)
    /* missing or not a string */;
printf("%s\n", YAJL_GET_STRING(name));
```

The `path` array contains object keys, not a dotted string and not array indexes. Example: `{"account", "profile", "lastname", NULL}`.

### Accessing arrays

The tree node exposes its array values through `YAJL_GET_ARRAY`:

```c
yajl_val arr = yajl_tree_get(root, (const char *[]) {"students", NULL}, yajl_t_array);
if (!arr) /* error */;
for (size_t i = 0; i < YAJL_GET_ARRAY(arr)->len; i++) {
    yajl_val item = YAJL_GET_ARRAY(arr)->values[i];
    /* check item is an object, then retrieve its keys */
}
```

You can also use `arr->u.array.len` and `arr->u.array.values[i]` after verifying `YAJL_IS_ARRAY(arr)`.

## 3. Streaming parser API

### Main functions

| Function | Purpose |
|---|---|
| `yajl_alloc(callbacks, alloc_funcs, ctx)` | Create parser and register event callbacks. |
| `yajl_config(handle, option, ...)` | Set parser options. |
| `yajl_parse(handle, jsonText, jsonTextLength)` | Feed one chunk of JSON bytes. Can be called repeatedly. |
| `yajl_complete_parse(handle)` | Tell YAJL the input is finished; catches incomplete final input. |
| `yajl_get_error(handle, verbose, jsonText, jsonTextLength)` | Allocate a human-readable parse error. |
| `yajl_free_error(handle, error_string)` | Free the error string returned by `yajl_get_error`. |
| `yajl_get_bytes_consumed(handle)` | Number of bytes consumed from the most recent chunk. |
| `yajl_status_to_string(status)` | Convert parser status to text. |
| `yajl_free(handle)` | Release parser. |

### Parser statuses

- `yajl_status_ok`: parsing succeeded so far.
- `yajl_status_client_canceled`: one of your callbacks returned 0.
- `yajl_status_error`: invalid JSON or parser error.

### Callback signatures

The `yajl_callbacks` struct has these members. All return `int`: return non-zero to continue, 0 to cancel.

```c
int (*yajl_null)(void *ctx);
int (*yajl_boolean)(void *ctx, int boolVal);
int (*yajl_integer)(void *ctx, long long integerVal);
int (*yajl_double)(void *ctx, double doubleVal);
int (*yajl_number)(void *ctx, const char *numberVal, size_t numberLen);
int (*yajl_string)(void *ctx, const unsigned char *stringVal, size_t stringLen);
int (*yajl_start_map)(void *ctx);
int (*yajl_map_key)(void *ctx, const unsigned char *key, size_t stringLen);
int (*yajl_end_map)(void *ctx);
int (*yajl_start_array)(void *ctx);
int (*yajl_end_array)(void *ctx);
```

Important:
- `ctx` is your own pointer. Pass a pointer to a struct holding counters or current state to `yajl_alloc`.
- `stringVal` and `key` are **length-delimited** and are not guaranteed to end with `\0`.
- If you set `yajl_number`, it receives all JSON numbers as text; otherwise YAJL may use integer/double callbacks where representable.

### Parser options (`yajl_config`)

- `yajl_allow_comments`
- `yajl_dont_validate_strings`
- `yajl_allow_trailing_garbage`
- `yajl_allow_multiple_values`
- `yajl_allow_partial_values`
- `yajl_allow_json5`

For strict standard JSON in an exam, do not enable relaxed options unless the statement asks for them.

## 4. Generator / serialization API

### Main functions

| Function | Purpose |
|---|---|
| `yajl_gen_alloc(allocFuncs)` | Create a generator. |
| `yajl_gen_config(handle, option, ...)` | Configure formatting/UTF-8/output options. |
| `yajl_gen_map_open` / `yajl_gen_map_close` | Start/end JSON object `{}`. |
| `yajl_gen_array_open` / `yajl_gen_array_close` | Start/end JSON array `[]`. |
| `yajl_gen_string(handle, bytes, len)` | Generate string value or object key. |
| `yajl_gen_integer(handle, number)` | Generate integer. |
| `yajl_gen_double(handle, number)` | Generate floating-point value. |
| `yajl_gen_number(handle, text, len)` | Generate a number from its text representation. |
| `yajl_gen_bool(handle, value)` | Generate true/false. |
| `yajl_gen_null(handle)` | Generate null. |
| `yajl_gen_get_buf(handle, &buffer, &length)` | Get generated output buffer. |
| `yajl_gen_clear(handle)` | Clear output buffer but keep generator state (streaming use). |
| `yajl_gen_reset(handle, separator)` | Reset generator state for a new JSON value; does not itself clear buffer. |
| `yajl_gen_free(handle)` | Release generator. |

### Generator options

- `yajl_gen_beautify`: pretty/indented output.
- `yajl_gen_indent_string`: custom indentation string.
- `yajl_gen_print_callback`: stream output through a callback.
- `yajl_gen_validate_utf8`: validate UTF-8 strings.
- `yajl_gen_escape_solidus`: escape `/` as `\\/`.
- `yajl_gen_json5`: allow JSON5 output (not strict JSON).

### Generator status values

`yajl_gen_status_ok`, `yajl_gen_keys_must_be_strings`, `yajl_max_depth_exceeded`, `yajl_gen_in_error_state`, `yajl_gen_generation_complete`, `yajl_gen_invalid_number`, `yajl_gen_no_buf`, `yajl_gen_invalid_string`.

## 5. Shared/custom allocation

Parser/generator allocation functions can be customized through `yajl_alloc_funcs`. For ordinary coursework, pass `NULL` so YAJL uses the C runtime allocator. Do not mix custom allocator ownership with plain `free` unless the matching allocator contract says to.

## 6. Identify YAJL vs Jansson quickly

| Clue | YAJL | Jansson |
|---|---|---|
| Header | `<yajl/yajl_parse.h>`, `<yajl/yajl_tree.h>`, `<yajl/yajl_gen.h>` | `<jansson.h>` |
| Linker flag | `-lyajl` | `-ljansson` |
| Parse-to-tree | `yajl_tree_parse` | `json_load_file` / `json_loads` |
| Object lookup | `yajl_tree_get`, `YAJL_GET_*` | `json_object_get`, `json_string_value`, `json_integer_value` |
| Free | `yajl_tree_free` | `json_decref` |
| Generate | `yajl_gen_*` | `json_dumps`, `json_dump_file` |

If your teacher's header is `<jansson.h>`, this YAJL reference is not the one to memorize. The name in your notes may have been “YAJL” or “Jansson”; the header settles it.

### Tiny Jansson recognition guide (only if the supplied header is `jansson.h`)

Jansson is another C JSON library, with a different tree API. Its common pattern looks like this:

```c
#include <jansson.h>
json_error_t error;
json_t *root = json_load_file("data.json", 0, &error);
if (root == NULL) {
    fprintf(stderr, "%s\n", error.text);
    return -1;
}
json_t *name_value = json_object_get(root, "name");
if (!json_is_string(name_value)) {
    json_decref(root);
    return -1;
}
printf("%s\n", json_string_value(name_value));
json_decref(root);
```

Recognize these Jansson functions: `json_load_file`, `json_loads`, `json_object_get`, `json_array_get`, `json_is_string`, `json_is_integer`, `json_string_value`, `json_integer_value`, `json_object_set_new`, `json_dumps`, `json_dump_file`, and `json_decref`. Its usual linker flag is `-ljansson`. Do not write Jansson calls in a YAJL project or vice versa.
