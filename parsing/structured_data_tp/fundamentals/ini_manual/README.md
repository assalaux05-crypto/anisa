# INI — manual parsing (2.5 pts)

Implement:
- `ini_get`: read a key from the requested section (1 pt).
- `ini_set`: replace an existing key or append it to the section (1 pt).
- `ini_delete`: remove a key from the section (0.5 pt).

Ignore blank lines and lines beginning with `#` or `;`. Trim spaces around section names, keys and values. Do not confuse a key in another section with the requested key.
