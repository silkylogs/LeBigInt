#include "lebigint.h"
#include "lebigint_handle.h"

/*
# LeBigInt - Implementation details
- Implement backing data as little endian number string
*/

static struct LbiSystemData {
	struct LeBigInt *handles;
	size_t handle_cnt;

	char *backing_buffer;
	size_t backing_buffer_sz;
};


void lbi_sys_init(void) {

}

void lbi_sys_cleanup(void) {

}

struct LeBigInt *lbi_from_int(intmax_t num) {
	// request new handle, return NaN on failure
	struct LeBigInt *handle = lbi_handle_new();
	if (handle->is_nan) return handle;

	// get sign
	// set sign
	handle->is_neg = (num < 0);
	
	if (handle->is_neg) num = -num;
	// get digit
	// append digit
	// div by 10
	// while num != 0
	while (num) {
		char digit = '0' + (num % 10);
		lbi_handle_append_digit(handle, digit);
		num /= 10;
	}

	// return handle
	return handle;
}

struct LeBigInt *lbi_from_zt_cstr(const char *);
struct LeBigInt *lbi_from_str(const char *, size_t);

void lbi_assign(struct LeBigInt *dst, struct LeBigInt *src);
void lbi_printf(const char *fmt, ...);
void lbi_drop(struct LeBigInt *, ...);

#define LBI_INDEX(T, ptr, idx) *((T)*)(lbi_ptr(sizeof ((T)), (ptr), (idx)))
void *lbi_ptr(size_t type_sz, uint8_t *ptr, struct LeBigInt *idx);

void lbi_add(struct LeBigInt *dst, struct LeBigInt *param);
void lbi_sub(struct LeBigInt *dst, struct LeBigInt *param);
void lbi_mul(struct LeBigInt *dst, struct LeBigInt *param);
void lbi_div(struct LeBigInt *dst, struct LeBigInt *param);
void lbi_mod(struct LeBigInt *dst, struct LeBigInt *param);

void lbi_add_int(struct LeBigInt *dst, intmax_t param);
void lbi_sub_int(struct LeBigInt *dst, intmax_t param);
void lbi_mul_int(struct LeBigInt *dst, intmax_t param);
void lbi_div_int(struct LeBigInt *dst, intmax_t param);
void lbi_mod_int(struct LeBigInt *dst, intmax_t param);

bool lbi_divisible_by_int(struct LeBigInt *, intmax_t);

void lbi_fwd_iter_end_inclusive_step_int(struct LeBigInt *it, struct LeBigInt *lim, intmax_t step);
void lbi_fwd_iter_end_noninclusive_step_int(struct LeBigInt *it, struct LeBigInt *lim, intmax_t step);
void lbi_bwd_iter_end_inclusive_step_int(struct LeBigInt *it, struct LeBigInt *lim, intmax_t step);
void lbi_bwd_iter_end_noninclusive_step_int(struct LeBigInt *it, struct LeBigInt *lim, intmax_t step);

void lbi_fwd_iter_end_inclusive_step(struct LeBigInt *it, struct LeBigInt *lim, struct LeBigInt *step);
void lbi_fwd_iter_end_noninclusive_step(struct LeBigInt *it, struct LeBigInt *lim, struct LeBigInt *step);
void lbi_bwd_iter_end_inclusive_step(struct LeBigInt *it, struct LeBigInt *lim, struct LeBigInt *step);
void lbi_bwd_iter_end_noninclusive_step(struct LeBigInt *it, struct LeBigInt *lim, struct LeBigInt *step);