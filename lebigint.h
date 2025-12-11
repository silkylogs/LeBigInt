#include <stdint.h>
#include <stdbool.h>

#ifndef LE_BIG_INT_2025_11_29_H
#define LE_BIG_INT_2025_11_29_H

/*
# LeBigInt - Little endian, arbitrary precision, signed Big Integer.

## Description
Intended to be a replacement for C's integral operations, with the goal of restricting behaviour to a wholly comprehensible subset. Specifiying intention is also another goal.

## Examples
### Standard integer math:
```c
void multiply_add(int *x, int multiplicand, int addend) {
	*x *= multiplicand;
	*x += addend;
}

int main() {
	int x, multiplicand, addend;

	x = 5;
	multiplicand = stoi("6");
	addend = stoi("7");

	multiply_add(&x, multiplicand, addend);

	printf("%d\n", x);

} // Automatic deallocation of stack variables
```

```c
void multiply_add(
	struct LeBigInt *x,
	struct LeBigInt *multiplicand,
	struct LeBigInt *addend
) {
	lbi_mul(x, multiplicand);
	lbi_add(x, addend);
}

int main() {
	struct LeBigInt *x, *multiplicand, *addend;

	x = lbi_from_int(5);
	multiplicand = lbi_from_zt_cstr("6"); // Note: NaN on failure?
	addend = lbi_from_str("7", sizeof "7");

	multiply_add(x, multiplicand, addend);

	lbi_printf("%lbi\n", result);

	lbi_drop(x);
	lbi_drop(multiplicand);
	lbi_drop(addend);
	lbi_drop(result);
}
```

### Iteration
```c
int i, limit;

i = 0;
limit = 100;

for (i = 0; i <= limit; i += stoi("1")) {
	if (i % 3 && i % 5) { printf("FizzBuzz\n"); }
	else if (i % 3) { printf("Fizz\n"); }
	else if (i % 5) { printf("Buzz\n"); }
	else { printf("%d\n", i); }
}
```

```c
struct LeBigInt *i, *limit;

i = lbi_from_int(0);
limit = lbi_from_int(100);

do {
	if (lbi_divisible_by_int(i, 3) && lbi_divisible_by_int(i, 5)) {
		lbi_printf("FizzBuzz\n");
	}
	else if (lbi_divisible_by_int(i, 3)) {
		lbi_printf("Fizz\n");
	}
	else if (lbi_divisible_by_int(i, 5)) {
		lbi_printf("Buzz\n");
	}
	else {
		lbi_printf("%lbi\n", i);
	}
} while (lbi_fwd_iter_end_inclusive_step_int(i, limit, 1));

lbi_drop(i, limit);
```

### Memory access
```c
size_t i;
char *bigstr = get_big_string();

for (
	i = 0;
	bigstr[i] != '\0';
	i += 1
) {
	putchar(bigstr[i]);
}
```

```c
struct LeBigInt *i;
char *bigstr = get_big_string();

for (
	i = lbi_from_int(0);
	LBI_INDEX(char, bigstr, i) != '\0';
	lbi_add(i, 1)
) {
	// Note: LBI_INDEX desugars to the following:
	putchar( *((char)*)lbi_ptr(sizeof (char), bigstr, i) );
}

lbi_drop(i);
```
*/


struct LeBigInt {
	char *magnitude; /* Null terminated string */
	size_t magnitude_sz; /* Includes null terminator */
	size_t magnitude_cap;
	bool is_nan;
	bool is_neg;
};

static struct LeBigInt lbi_nan = { "NaN", sizeof "NaN", sizeof "NaN", true, false };

struct LeBigInt lbi_from_int(intmax_t);
struct LeBigInt lbi_from_zt_cstr(const char *);
struct LeBigInt lbi_from_str(const char *, size_t);

void lbi_assign(struct LeBigInt *dst, struct LeBigInt src);
void lbi_printf(const char *fmt, ...);
void lbi_drop(struct LeBigInt);

#define LBI_INDEX(T, ptr, idx) *((T)*)(lbi_ptr(sizeof ((T)), (ptr), (idx)))
void *lbi_ptr(size_t type_sz, uint8_t *ptr, struct LeBigInt *idx);

void lbi_add(struct LeBigInt *dst, struct LeBigInt param);
void lbi_sub(struct LeBigInt *dst, struct LeBigInt param);
void lbi_mul(struct LeBigInt *dst, struct LeBigInt param);
void lbi_div(struct LeBigInt *dst, struct LeBigInt param);
void lbi_mod(struct LeBigInt *dst, struct LeBigInt param);

void lbi_add_int(struct LeBigInt *dst, intmax_t param);
void lbi_sub_int(struct LeBigInt *dst, intmax_t param);
void lbi_mul_int(struct LeBigInt *dst, intmax_t param);
void lbi_div_int(struct LeBigInt *dst, intmax_t param);
void lbi_mod_int(struct LeBigInt *dst, intmax_t param);

bool lbi_divisible_by_int(struct LeBigInt, intmax_t);

void lbi_fwd_iter_end_inclusive_step_int	(struct LeBigInt *it, struct LeBigInt lim, intmax_t step);
void lbi_fwd_iter_end_noninclusive_step_int	(struct LeBigInt *it, struct LeBigInt lim, intmax_t step);
void lbi_bwd_iter_end_inclusive_step_int	(struct LeBigInt *it, struct LeBigInt lim, intmax_t step);
void lbi_bwd_iter_end_noninclusive_step_int	(struct LeBigInt *it, struct LeBigInt lim, intmax_t step);

void lbi_fwd_iter_end_inclusive_step	(struct LeBigInt *it, struct LeBigInt lim, struct LeBigInt step);
void lbi_fwd_iter_end_noninclusive_step	(struct LeBigInt *it, struct LeBigInt lim, struct LeBigInt step);
void lbi_bwd_iter_end_inclusive_step	(struct LeBigInt *it, struct LeBigInt lim, struct LeBigInt step);
void lbi_bwd_iter_end_noninclusive_step	(struct LeBigInt *it, struct LeBigInt lim, struct LeBigInt step);

#endif
