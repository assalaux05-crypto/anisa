# libporco

A small helper library provided as a compiled archive (`libporco.a`) and
its header (`porco.h`). You are not meant to see or reimplement what is
inside; only rely on the contract documented here.

## `double porco_knots_to_ms(double knots);`

Converts a speed from knots to meters per second.

- On success, returns `knots * 0.5144444...` (the standard nautical
  conversion factor, `1852.0 / 3600.0`).
- If `knots` is negative, returns `-1.0`. This is a normal, documented
  outcome, not an error to hide: let it through unchanged.

## `const char *porco_machine_class(double speed_ms);`

Classifies a speed already expressed in meters per second.

- Returns `"INVALID"` if `speed_ms` is negative.
- Returns `"FAST"` if `speed_ms >= 40.0`.
- Returns `"STANDARD"` otherwise.

The returned string is owned by the library: never free it or write to it.

## `int porco_parse_code(const char *code);`

Validates and decodes a workshop registration code.

A valid code is **exactly one uppercase letter followed by exactly two
decimal digits** (e.g. `"S21"`, `"M09"`, `"X07"`). On success, returns the
two-digit number as an `int` (e.g. `"X07"` -> `7`).

Returns `-1` for any invalid code: wrong length, wrong character kinds
(e.g. `"XX7"` has a second letter instead of a digit), or a `NULL`
pointer. `-1` is the documented sentinel for "invalid code".

## `int porco_write_machine_label(char *buffer, size_t size, const char *name, double speed_ms);`

Writes a display label for a machine into `buffer` (a caller-provided
buffer of `size` bytes), the same way `snprintf` would: the write is
always safely truncated to fit `size`, and the return value is the
number of characters that would have been written if `size` had been
large enough (excluding the terminating `'\0'`), regardless of whether
truncation occurred.

Returns `-1` without touching `buffer` if `buffer` or `name` is `NULL`.

`speed_ms` is accepted for future extension of the label format and does
not currently change the produced text.
