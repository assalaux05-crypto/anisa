# JSON library quick reference — choose the one your teacher gives you

The exam direction is fixed: **CSV is manual parsing; JSON uses a library.** The exact JSON library has not been confirmed. Do not assume that the teacher will use cJSON. In C there is no single standard JSON API, so the important skill is to learn the same operations in the library that appears in the TP.

## 1. Recognize the library from its header

| Library | Typical header | Main parsed value type | Usual parse entry point |
|---|---|---|---|
| cJSON | `#include <cjson/cJSON.h>` (some installations use `cJSON.h`) | `cJSON *` | `cJSON_Parse()` after reading file text |
| json-c | `#include <json-c/json.h>` | `struct json_object *` | `json_object_from_file()` or `json_tokener_parse()` |
| Jansson | `#include <jansson.h>` | `json_t *` | `json_load_file()` |
| Parson | `#include "parson.h"` | `JSON_Value *` | `json_parse_file()` |

The header name and compile flags depend on installation. Look at the teacher's include line, provided Makefile and examples first. A library can be given as source files (`.c` + `.h`) rather than preinstalled.

## 2. The universal JSON workflow

1. Parse the document. Parsing validates JSON syntax and creates a tree of JSON values in memory.
2. Check the parse result. A null pointer usually means failure.
3. Navigate from the root: object → key → array → index → object → key.
4. Check the type before reading a value. A JSON string is not the same as a number written inside quotes.
5. Copy needed values into your own C variables or structs. Do not keep pointers into the JSON tree after freeing it.
6. Release the root tree exactly once using the library's cleanup function.
7. For modifications, construct/change the JSON tree with library functions and serialize it. Never create JSON by concatenating strings manually.

## 3. Mapping: same task, different APIs

| Operation | cJSON | json-c | Jansson | Parson |
|---|---|---|---|---|
| Parse file | read text + `cJSON_Parse` | `json_object_from_file` | `json_load_file` | `json_parse_file` |
| Get object key | `cJSON_GetObjectItemCaseSensitive` | `json_object_object_get_ex` | `json_object_get` | `json_object_get_value` / typed getter |
| Check string | `cJSON_IsString` | `json_object_is_type(..., json_type_string)` | `json_is_string` | `json_value_get_type` or typed getter |
| Get string | `cJSON_GetStringValue` / `valuestring` | `json_object_get_string` | `json_string_value` | `json_object_get_string` |
| Check number | `cJSON_IsNumber` | `json_object_is_type(..., json_type_int/double)` | `json_is_number` | `json_value_get_type` / typed getter |
| Get number | `cJSON_GetNumberValue` / `valuedouble` | `json_object_get_double` | `json_number_value` / `json_integer_value` | `json_object_get_number` |
| Array length | `cJSON_GetArraySize` | `json_object_array_length` | `json_array_size` | `json_array_get_count` |
| Array element | `cJSON_GetArrayItem` | `json_object_array_get_idx` | `json_array_get` | `json_array_get_value` / `json_array_get_object` |
| Free parsed root | `cJSON_Delete` | `json_object_put` | `json_decref` | `json_value_free` |
| Serialize | `cJSON_Print` | `json_object_to_json_string_ext` | `json_dumps` | `json_serialize_to_string_pretty` |

This is a first-pass mapping, not a complete API manual. Read the actual installed header/documentation for exact signatures and ownership rules.

## 4. Minimal parse-and-count pattern for each library

The following fragments show the same operation: parse a file, get the root object's `courses` array, count it, and free the root. They are short API orientation examples; check return types and ownership against the installed library version.

### cJSON

cJSON parses a string, so first read the file into a null-terminated buffer (the longer `read_file()` helper is shown in the struct example below):

```c
cJSON *root = cJSON_Parse(text);
const cJSON *courses = cJSON_GetObjectItemCaseSensitive(root, "courses");
if (cJSON_IsArray(courses))
    count = (size_t)cJSON_GetArraySize(courses);
cJSON_Delete(root);
```

### Jansson

```c
json_error_t error;
json_t *root = json_load_file(path, 0, &error);
if (root == NULL)
    return 0;
if (!json_is_object(root)) { json_decref(root); return 0; }
json_t *courses = json_object_get(root, "courses");
if (!json_is_array(courses)) { json_decref(root); return 0; }
count = json_array_size(courses);
json_decref(root);
```

### json-c

```c
struct json_object *root = json_object_from_file(path);
struct json_object *courses = NULL;
if (root == NULL)
    return 0;
if (!json_object_object_get_ex(root, "courses", &courses) ||
    !json_object_is_type(courses, json_type_array)) {
    json_object_put(root);
    return 0;
}
count = json_object_array_length(courses);
json_object_put(root);
```

### Parson

```c
JSON_Value *root = json_parse_file(path);
JSON_Object *object;
JSON_Array *courses;
if (root == NULL)
    return 0;
object = json_value_get_object(root);
if (object == NULL) { json_value_free(root); return 0; }
courses = json_object_get_array(object, "courses");
if (courses == NULL) { json_value_free(root); return 0; }
count = json_array_get_count(courses);
json_value_free(root);
```

Remember: Jansson's `json_object_get` and `json_array_get` return borrowed values that stay alive while the root is alive. json-c uses reference counting and the root is released with `json_object_put`. Parson's parsed root is released with `json_value_free`. cJSON's parsed root is released with `cJSON_Delete`.

## 5. The important part: extract a complete JSON object block into a C struct

Suppose the JSON file contains:

```json
{
  "courses": [
    {
      "id": 10,
      "title": "C Programming",
      "teacher": { "name": "Dr. Ali", "room": "B12" },
      "students": [
        { "id": 1, "name": "Manel", "grade": 18.5 },
        { "id": 2, "name": "Yacine", "grade": 14.0 }
      ]
    }
  ]
}
```

First define your C structures:

```c
typedef struct {
    int id;
    char name[64];
    double grade;
} Student;

typedef struct {
    int id;
    char title[64];
    char teacher_name[64];
    char teacher_room[32];
    Student students[16];
    size_t student_count;
} Course;
```

**The key idea:** the library does not magically fill `Course`. You navigate to the JSON object, read each member, check its type, and copy its values into the fields of your struct. The `students` array becomes `students[0]`, `students[1]`, and so on.

### Example using cJSON

This is an illustrative implementation pattern. Adapt the header path and compiler flags to your environment.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

static char *read_file(const char *path)
{
    FILE *fp = fopen(path, "rb");
    char *buffer;
    long length;

    if (fp == NULL)
        return NULL;
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return NULL; }
    length = ftell(fp);
    if (length < 0 || fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return NULL; }
    buffer = malloc((size_t)length + 1);
    if (buffer == NULL) { fclose(fp); return NULL; }
    if (fread(buffer, 1, (size_t)length, fp) != (size_t)length) {
        free(buffer);
        fclose(fp);
        return NULL;
    }
    buffer[length] = '\0';
    fclose(fp);
    return buffer;
}

int extract_course(const char *path, int wanted_id, Course *out)
{
    char *text;
    cJSON *root;
    const cJSON *courses;
    const cJSON *course = NULL;
    const cJSON *item;
    const cJSON *value;
    int found = 0;

    if (path == NULL || out == NULL)
        return 0;
    text = read_file(path);
    if (text == NULL)
        return 0;
    root = cJSON_Parse(text);
    free(text);
    if (root == NULL)
        return 0;

    courses = cJSON_GetObjectItemCaseSensitive(root, "courses");
    if (!cJSON_IsArray(courses))
        goto cleanup;

    cJSON_ArrayForEach(item, courses) {
        const cJSON *id;
        if (!cJSON_IsObject(item))
            continue;
        id = cJSON_GetObjectItemCaseSensitive(item, "id");
        if (cJSON_IsNumber(id) && id->valuedouble == wanted_id) {
            course = item;
            found = 1;
            break;
        }
    }
    if (!found)
        goto cleanup;

    /* Read scalar fields from the chosen course object. */
    value = cJSON_GetObjectItemCaseSensitive(course, "id");
    if (!cJSON_IsNumber(value)) goto cleanup;
    out->id = (int)value->valuedouble;

    value = cJSON_GetObjectItemCaseSensitive(course, "title");
    if (!cJSON_IsString(value) || value->valuestring == NULL) goto cleanup;
    if (snprintf(out->title, sizeof(out->title), "%s", value->valuestring) >= (int)sizeof(out->title)) goto cleanup;

    /* Go one level deeper: course.teacher.name and course.teacher.room. */
    value = cJSON_GetObjectItemCaseSensitive(course, "teacher");
    if (!cJSON_IsObject(value)) goto cleanup;
    {
        const cJSON *name = cJSON_GetObjectItemCaseSensitive(value, "name");
        const cJSON *room = cJSON_GetObjectItemCaseSensitive(value, "room");
        if (!cJSON_IsString(name) || !cJSON_IsString(room)) goto cleanup;
        if (snprintf(out->teacher_name, sizeof(out->teacher_name), "%s", name->valuestring) >= (int)sizeof(out->teacher_name)) goto cleanup;
        if (snprintf(out->teacher_room, sizeof(out->teacher_room), "%s", room->valuestring) >= (int)sizeof(out->teacher_room)) goto cleanup;
    }

    /* Convert the JSON students array into the C students[] array. */
    value = cJSON_GetObjectItemCaseSensitive(course, "students");
    if (!cJSON_IsArray(value)) goto cleanup;
    out->student_count = 0;
    cJSON_ArrayForEach(item, value) {
        const cJSON *sid;
        const cJSON *name;
        const cJSON *grade;
        size_t n = out->student_count;
        if (n >= 16) goto cleanup;
        if (!cJSON_IsObject(item)) goto cleanup;
        sid = cJSON_GetObjectItemCaseSensitive(item, "id");
        name = cJSON_GetObjectItemCaseSensitive(item, "name");
        grade = cJSON_GetObjectItemCaseSensitive(item, "grade");
        if (!cJSON_IsNumber(sid) || !cJSON_IsString(name) || !cJSON_IsNumber(grade)) goto cleanup;
        out->students[n].id = (int)sid->valuedouble;
        if (snprintf(out->students[n].name, sizeof(out->students[n].name), "%s", name->valuestring) >= (int)sizeof(out->students[n].name)) goto cleanup;
        out->students[n].grade = grade->valuedouble;
        out->student_count++;
    }

    cJSON_Delete(root);
    return 1;

cleanup:
    cJSON_Delete(root);
    return 0;
}
```

Notice the navigation pattern:

```text
root
 └── courses (array)
      └── element i (object)
           ├── id       → Course.id
           ├── title    → Course.title
           ├── teacher (object)
           │    ├── name → Course.teacher_name
           │    └── room → Course.teacher_room
           └── students (array)
                └── element j (object)
                     ├── id    → Course.students[j].id
                     ├── name  → Course.students[j].name
                     └── grade → Course.students[j].grade
```

### What changes with other libraries?

The algorithm and your `struct` definitions stay the same. Only the JSON API calls change. For example, with Jansson you would use `json_load_file`, `json_object_get`, `json_is_array`, `json_array_size`, `json_array_get`, `json_is_string`, `json_string_value`, and finally `json_decref`. With json-c you would use `json_object_from_file`, `json_object_object_get_ex`, `json_object_is_type`, `json_object_array_length`, `json_object_array_get_idx`, and `json_object_put`. With Parson you would use `json_parse_file`, `json_value_get_object`, `json_object_get_value`, `json_value_get_array`, `json_array_get_count`, typed getters, and `json_value_free`.

## 6. Build flags: discover, do not guess

If the teacher gives a Makefile, follow it. Otherwise check whether pkg-config knows the library:

```sh
pkg-config --list-all | grep -i json
pkg-config --cflags --libs json-c
pkg-config --cflags --libs jansson
```

For cJSON or Parson, installation style differs: the teacher may provide a header/source pair, or a system package. If the library is a source pair, compile its `.c` file with your exercise. The Makefiles in the exercises accept `JSON_CFLAGS` and `JSON_LIBS` so you can pass the flags supplied by the teacher.

