# Exercise 1 — decimal CSV field to unsigned — 10 points

**Prototype (keep exactly):**
```c
unsigned parse_unit(char *decimal);
```

The fixture `units.csv` has a header and one decimal value per row. Implement `parse_unit` using `atoi` and return the result as `unsigned`. The main reads each row and calls your function.

Scope: values are valid non-negative decimal integers that fit the expected `unsigned` range. For this exam-style exercise, NULL or an empty string may return 0. `atoi` is intentionally requested by the remembered statement; for production code, `strtoul` with range/error checking is safer.

Expected fixture values: `12`, `0`, `255`, `1024`, `42`.

Build: `make && ./test`
