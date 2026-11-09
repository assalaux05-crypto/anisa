# CSV reference solutions

Attempt each exercise first. The complete source files are also in `solutions/csv/`.

## Exercice 1

```c
unsigned parse_unit(char *decimal)
{
    if (decimal == NULL)
        return 0;
    return (unsigned)atoi(decimal);
}
```

This intentionally mirrors the remembered exam request. `atoi` returns `int`; the cast converts it to `unsigned`. This assumes the exam's positive, in-range input. A production parser should use `strtoul` and check errors/range.

## Exercice 2 — cursor logic

- Search for comma, newline or NUL.
- Return the start pointer directly.
- Find the next comma or line ending and replace it with `\0`.
- If comma was found, move cursor one character forward.
- Otherwise set cursor to NULL because the last field was consumed.
- The returned pointer is borrowed from the row buffer; do not free it.

The solution preserves empty fields, including a final empty field after a trailing comma.

## Exercice 3 — relation between two CSV files

- `parse_author_row`: parse ID and name, allocate `struct author`, convert ID using `atoi`.
- `print_all_books_written_by`: scan authors to find the last name and ID; then scan books and print rows with matching `author_id`.
- Free every temporary field and the allocated author object.

The reference code assumes the exact simple, unquoted CSV subset in the fixtures.
