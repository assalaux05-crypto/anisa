# Exercise 03 — Sum numeric values in an array of objects

**Difficulty:** Level 1 — Easy  
**Points:** 2.0 pts  
**Function to implement:** `json_sum_prices`

## Statement

Calculate the sum of products[].price. Each price must be a JSON number; fail on missing/wrong-type price.

## Required prototype

```c
int json_sum_prices(const char *path, double *sum);
```

## Suggested solution steps

1. Parse root and get products array.
2. Loop from 0 to array length - 1.
3. Get each item as an object; get price and check number type.
4. Accumulate as double, free root and store result.

## Useful predefined functions / library API

array size/get; object get; is-number; number-value; free root.

**Important:** Use the JSON library specified by your teacher. The task is written independently of one particular API; translate the operations above to the library available in the TP. See `docs/JSON_LIBRARY_QUICK_REFERENCE.md`.

## Cases you must test

Empty array; price missing; string "1200"; null price; nested element not object.

## Expected result for the supplied fixture

Sum is 5200.5.

## Build and run

```sh
make
./test
make clean
```

The implementation file is intentionally a compilable TODO stub. The provided `main.c` is a starting test harness; add more tests before submitting.
