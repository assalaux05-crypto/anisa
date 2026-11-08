# Structured Data — C Programming TP

This is a practice TP scaffold plus a detailed learning guide.

**Start here:** open `structured_data_tp.html` in a browser. It explains the purpose and solution plan for every function prototype, the standard C functions used in manual parsing, the library APIs for libcsv/cJSON/libyaml/SQLite, and a complete JSON-to-`struct` example.

## Layout

- `fundamentals/`: small manual parsing exercises using standard C functions, plus SQLite CRUD.
- `proficiencies/`: library exercises for CSV (`libcsv`), JSON (`cJSON`) and YAML (`libyaml`).
- Each exercise folder contains its own `exercise.h`, TODO implementation `.c`, supplied `main.c`, fixture file(s), Makefile and short README.

## Compile an exercise

```sh
cd fundamentals/csv_manual
make
./exo
make clean
```

For the SQLite exercise, create the database first:

```sh
cd fundamentals/sql_manual
sqlite3 school.db < school.sql
make
./exo
```

The library exercises need the matching development packages and link flags; see the HTML guide.

## Important

The `.c` implementation files are TODO placeholders. The mains, headers, fixtures and Makefiles are supplied; the functions still need to be implemented. The manual JSON/YAML/TOML/XML tasks intentionally support only the small subsets described in their READMEs, not the complete file-format specifications.
