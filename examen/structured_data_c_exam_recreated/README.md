# Structured Data C — Recreated TP Exam

This pack is based on the exam details remembered by the student. It deliberately contains **exactly three CSV fundamentals exercises**. JSON proficiencies are a preparation section because the exact original JSON prompt was not remembered.

## Repository

```text
structured_data_c_exam_recreated/
├── README.md
├── SUBJECT.html
├── LAST_MINUTE_PLAN.md
├── YAJL_API_REFERENCE.md
├── YAJL_WORKED_PATTERNS.md
├── JSON_EXERCISE_BANK.md
├── fundamentals/
│   ├── ex01_unsigned/
│   ├── ex02_parse_field/
│   └── ex03_authors_books/
├── proficiencies/
│   ├── ex01_tree_config/
│   ├── ex02_tree_students/
│   ├── ex03_stream_callbacks/
│   ├── ex04_generate_json/
│   └── ex05_transform_json/
└── solutions/
    ├── CSV_SOLUTIONS.md
    └── csv/ (complete reference implementations)
```

## The three CSV fundamentals exercises

1. **Unsigned conversion:** `unsigned parse_unit(char *decimal)` — convert a decimal CSV field with `atoi`.
2. **CSV field parser:** `char *parse_field(char **input)` — return a pointer into the writable row, replace the separator with `\0`, and advance the cursor; the returned field is borrowed, not heap-allocated.
3. **Author/book relation:** `struct author *parse_author_row(char *row)` plus `void print_all_books_written_by(char *author_lastname)` — parse `id,lastname` and match the author to book rows in a second CSV.

The CSV parser in exercise 2 intentionally handles the simple comma-separated subset in the fixture: no quoted commas or escaped quotes. The actual exam may have had fewer edge cases; the README makes the contract unambiguous for practice.

## JSON library name: YAJL or Jansson?

Your note says **“JAJL”**. The closest library name is probably **YAJL** (“Yet Another JSON Library”). Verify the header if you can:

- YAJL: `#include <yajl/yajl_tree.h>` / `yajl_parse.h` / `yajl_gen.h`, link with `-lyajl`.
- Jansson (a different library): `#include <jansson.h>`, link with `-ljansson`.

This pack's JSON preparation is for **YAJL**. Do not mix the APIs. `YAJL_API_REFERENCE.md` lists its main public functions and macros. If the supplied header says `jansson.h`, use the short identification note in that document and tell me; the API is different.

## Build CSV exercise

```sh
cd fundamentals/ex01_unsigned
make
./test
```

Each folder builds independently using strict C99 warning flags. The exercise source files contain TODO stubs. Complete model CSV solutions are placed separately in `solutions/` so the subject does not reveal them.

## YAJL dependency

On Debian/Kali:
```sh
sudo apt update
sudo apt install libyajl-dev
```

Compile a YAJL exercise with:
```sh
cc -std=c99 -Wall -Wextra -Werror -pedantic -Wvla main.c exercise.c -lyajl -o test
```

The YAJL examples use three approaches:
- **Tree/DOM:** parse a full in-memory JSON string, then navigate its nodes.
- **Streaming callbacks:** receive events while YAJL parses chunks of JSON.
- **Generator:** build JSON output using typed generator calls.

YAJL is event-driven and supports incremental parsing; its tree interface is a convenience for smaller JSON documents. See the API reference and worked patterns.

## Moulinette-style rules

Keep prototypes unchanged. Check NULL pointers, `fopen`/read/write failures, malformed data, output buffer sizes and numeric conversion. Free every allocation and YAJL handle/tree/generator. A string callback receives a pointer and a length; do not assume it is NUL-terminated. Finalize a streaming parse with `yajl_complete_parse`.
