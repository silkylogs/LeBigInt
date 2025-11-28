#ifndef LE_BIG_INT_2025_11_28_H
#define LE_BIG_INT_2025_11_28_H

/*
# LeBigInt - Little endian, arbitary precision, signed Big Integer.

## Description
Intended to be a replacement for C's integral operations, with the goal of restricting behaviour to a wholly comprehensible subset.

## Examples
### Standard integer math:
```c
int multiply_add(int x, int multiplicand, int addend) {
	x *= multiplicand;
	x += addend;
	return x;
}

int x = 5;
int multiplicand = 6.0f;
int addend = stoi("7"); /* Possible failure: NaN propagation? */
int result = 0;

result = multiply_add(x, multiplicand, addend);

printf("%d\n", result);
```

```c
struct LeBigInt *
multiply_add(
	struct LeBigInt *x,
	struct LeBigInt *multiplicand,
	struct LeBigInt *addend
) {
	lbi_mul(x, multiplicand);
	lbi_add(x, addend);
	return x;
}

struct LeBigInt *x, *multiplicand, *addend, *result;

lbi_from_int32(x, 5);
lbi_from_float32(x, 6.0f);
lbi_from_cstr(x, "7");
lbi_from_int64(result, 0);

lbi_assign(result, multiply_add(x, multiplicand, addend));

lbi_printf("%lbi\n", result);

lbi_drop(x, multiplicand, addend, result);
```

### Iteration
```c
int i = 0;
int limit = 100;

for (i = 0; i <= limit; i += stoi("1")) {
	if (i % 3 && i % 5) { printf("FizzBuzz\n"); }
	else if (i % 3) { printf("Fizz\n"); }
	else if (i % 5) { printf("Buzz\n"); }
	else { printf("%d\n", i); } 
}
```

```c
struct LeBigInt *i. limit;

lbi_from_int32(i, 0);
lbi_from_int32(i, 100);

while (lbi_fwd_iter_end_inclusive_i32(i, limit, 1)) {
	if (lbi_mod_i32(i, 3) && lbi_mod_i32(i, 5)) { printf("FizzBuzz\n"); }
	else if (lbi_mod_i32(i, 3)) { printf("Fizz\n"); }
	else if (lbi_mod_i32(i, 5)) { printf("Buzz\n"): }
	else { lbi_printf("%lbi\n", i); }
}

lbi_drop(i, limit);
```

### Memory access
```c
size_t i;
char *bigstr = get_big_string();
for (i = 0; bigstr[i] != '\0'; i += 1) putchar(bigstr[i]);
```

```c
struct LeBigInt *i;
char *bigstr = get_big_string();
char c;

for (
	lbi_from_i32(i, 0); 
	lbi_index(char, bigstr, i) != '\0'; 
	lbi_add(i, 1)
) {
	c = *((char)*)lbi_index_desugared(sizeof (char), bigstr, i);
	putchar(c);
}

lbi_drop(i);
```
*/

#endif