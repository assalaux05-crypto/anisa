# Structured Data Parsing — Full Practice TP

This repository follows the teacher's clarified exam direction:

- **Part I — CSV:** manual parsing only. Do not use a CSV parsing library.
- **Part II — JSON:** use a JSON library. The exact library is not yet confirmed, so exercises are library-neutral and the reference guide compares common C APIs and includes parse-and-count examples for cJSON, json-c, Jansson and Parson.

There are **40 independent exercises**: 20 CSV and 20 JSON, arranged from easy to expert. Every exercise has a statement, prototype, suggested method, useful functions/APIs, edge cases, starter `.c`, `.h`, `main.c`, fixture and Makefile.

## Directory

```text
structured_parsing_mock_exam/
├── README.md
├── EXAM.html
├── part_1_csv_manual/
│   ├── common_types.h
│   └── csv_01_.../ through csv_20_.../
├── part_2_json_library/
│   ├── common_types.h
│   └── json_01_.../ through json_20_.../
└── docs/
    ├── CSV_MANUAL_PARSING.md
    └── JSON_LIBRARY_QUICK_REFERENCE.md
```

## How to work

1. Open the folder for one exercise. Read its `README.md` first.
2. Inspect the `.csv` or `.json` fixture. Draw its structure on paper.
3. Implement only the function declared in `exercise.h`. Keep the supplied prototype.
4. Add tests to `main.c` for every edge case listed in the README.
5. Run `make`, then `./test`, then `make clean`.
6. Do not move to the next level until the current one works with malformed and boundary inputs.

## Important about the JSON library

The JSON stubs compile without an external dependency so that the pack can be opened immediately. When implementing a JSON exercise, include the header of the library provided by the teacher and add its build flags. Do not implement a JSON parser manually in Part II. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Build example

```sh
cd part_1_csv_manual/csv_01_count_records
make
./test
make clean
```

The starter `exercise.c` files are intentionally TODO stubs. Their return values are placeholders, not the expected exercise results. The README in each folder gives the correct expected behavior.
