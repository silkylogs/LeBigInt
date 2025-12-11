#include "lebigint.h"

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/*
# LeBigInt - Implementation details
- Implement backing data as little endian number string
*/

/*
Try to append a digit. If allocation fails, handle is set to NaN.
*/
static void lbi_append_digit(struct LeBigInt *handle, char digit) {
	const size_t GROWTH_FACTOR = 2;
	char *ptr;

	/* Size exceeds capacity */
	if (handle->magnitude_sz >= handle->magnitude_cap) {
		handle->magnitude_cap *= GROWTH_FACTOR;
		ptr = realloc(handle->magnitude, handle->magnitude_cap);
		
		if (!ptr) {
			free(handle->magnitude);
			*handle = lbi_nan;
			return;
		}

		handle->magnitude = ptr;
	}

	handle->magnitude[handle->magnitude_sz - 1] = digit;
	handle->magnitude_sz += 1;
	handle->magnitude[handle->magnitude_sz - 1] = '\0';
}

/* 
You should not use a bigint after it's freed.
Hence I'm not going to do anything other than free the backing memory.
*/
void lbi_drop(struct LeBigInt to_free) {
	free(to_free.magnitude);
}

static bool lbi_init(struct LeBigInt *handle) {
	memset(handle, 0, sizeof (*handle));
	handle->magnitude = malloc(1);
	if (handle->magnitude) {
		handle->magnitude[0] = '\0';
		handle->magnitude_sz = 1;
		handle->magnitude_cap = 1;
		handle->is_nan = false;
		handle->is_neg = false;

		return true;
	}

	return false;
}

struct LeBigInt lbi_from_int(intmax_t num) {
	struct LeBigInt handle;

	if (!lbi_init(&handle)) return lbi_nan;

	// get sign
	// set sign
	handle.is_neg = (num < 0);
	
	if (handle.is_neg) num = -num;
	// get digit
	// append digit
	// div by 10
	// while num != 0
	while (num) {
		char digit = '0' + (num % 10);
		lbi_append_digit(&handle, digit);
		num /= 10;
	}

	// return handle
	return handle;
}
