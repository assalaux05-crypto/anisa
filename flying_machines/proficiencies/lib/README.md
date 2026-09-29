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

---

# libhangar

A second helper library, richer than `libporco`: a dynamically allocated,
opaque, generic container (`HangarList`), provided as a compiled archive
(`libhangar.a`) and its header (`hangar.h`). Only rely on the documented
API below; the internal layout of `HangarList` is not part of the
contract and may change.

## `HangarList *hangar_create(size_t element_size, HangarDestroyFn destroy);`

Creates an empty list whose elements are each `element_size` bytes.
`destroy` may be `NULL` if elements own no dynamically allocated memory;
otherwise it is called once per stored element when `hangar_destroy` runs.

Returns `NULL` on allocation failure or if `element_size` is `0`.

## `int hangar_push(HangarList *list, const void *element);`

Copies exactly `element_size` bytes from `element` into the container
(growing its internal storage as needed). Any dynamically allocated
memory reachable through the copied element (e.g. a `char *` field)
remains **your** responsibility: it must be released by the destructor
you registered.

Returns `0` on success, `-1` on failure (`list`/`element` `NULL`, or
allocation failure) — in which case nothing was pushed and the caller
still owns `element`'s resources.

## `size_t hangar_size(const HangarList *list);`

Returns the number of stored elements, or `0` if `list` is `NULL`.

## `void *hangar_at(HangarList *list, size_t index);` / `const void *hangar_at_const(const HangarList *list, size_t index);`

Returns a pointer to the element at `index`, or `NULL` if `list` is
`NULL` or `index` is out of bounds. Use `hangar_at_const` on a
`const HangarList *`.

## `int hangar_sort(HangarList *list, HangarCompareFn compare);`

Sorts the list in place using `compare` (same contract as `qsort`'s
comparator: negative if `a` sorts before `b`, positive if after, `0` if
equivalent).

Returns `0` on success, `-1` if `list` or `compare` is `NULL`. On
failure, the list is left unchanged.

## `void hangar_destroy(HangarList *list);`

Calls the registered destructor (if any) once per element, then frees
the container itself. Safe to call with `list == NULL` (no-op).
