# Manual CSV parsing — revision checklist

Part I must be implemented manually. `fopen`, `fgets`, `fgetc`, `fputc`, `fputs`, `fprintf`, `strtol`, `strtod`, `strcmp`, `memcpy`, `malloc`, `realloc` and `free` are ordinary C helpers; they do not parse CSV for you.

## Start with the simple format

A CSV file usually has a header followed by records. Commas separate fields, but empty fields still count:

```csv
id,name,grade
1,Ada,18
2,,15
3,Cleo,
```

There are 3 fields in every row. Do not treat an empty value as if the field did not exist.

## Why splitting on every comma is not enough

```csv
id,name,note
7,"Doe, Jane","She said ""hello"""
```

The comma inside the quotes is data, not a separator. Two consecutive quotes inside a quoted field mean one literal quote. For this reason, `strtok(line, ",")` is not a correct general CSV parser: it cannot understand quoted commas and it also modifies the source string.

## The four-state parser idea

For robust records, track one of these states:

- `FIELD_START`: beginning of a field; quote may open a quoted field.
- `UNQUOTED`: ordinary characters; comma ends the field.
- `QUOTED`: commas and newlines are data; doubled quote is an escaped quote.
- `AFTER_QUOTE`: the closing quote was found; only comma or record ending is valid.

For multiline records, read with `fgetc` and stop at newline only when outside a quoted field. Keep the buffer bounds checked on every character.

## Numeric conversion pattern

Use `strtol` / `strtod`, not `atoi` / `atof`, when invalid input matters:

```c
char *end = NULL;
long value;
errno = 0;
value = strtol(text, &end, 10);
if (text == end || errno == ERANGE) {
    /* no number or overflow */
}
while (*end != '\0' && isspace((unsigned char)*end))
    end++;
if (*end != '\0') {
    /* trailing non-space characters */
}
```

Also include `<errno.h>`, `<ctype.h>` and `<limits.h>` as needed.

## Writing CSV correctly

A field needs quotes when it contains comma, double quote, CR or LF. When quoted, double each embedded quote. Always close files and check I/O errors. For updates/deletes, write to a new file; do not truncate the input before reading it.
