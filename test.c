#include "lebigint.h"
#include "lebigint_handle.h"
#include "Prober/prober.h"

#include <string.h>

static bool test_lbi_from_int(void) {
	struct LeBigInt expected;
	struct LeBigInt *got;

	expected.magnitude = "0987654321";
	expected.magnitude_cnt = (sizeof "0987654321") - 1;
	expected.is_nan = false;
	expected.is_neg = true;

	lbi_sys_init();
	got = lbi_from_int(-1234567890);
	lbi_sys_cleanup();

	return
		0 == memcmp(expected.magnitude, got->magnitude, got->magnitude_cnt)
		&& expected.magnitude_cnt == got->magnitude_cnt
		&& expected.is_nan == got->is_nan
		&& expected.is_neg == got->is_neg;
}

int main(void) {
	PROBER_ADD_TEST(test_lbi_from_int);
	PROBER_RUN_TESTS();
	return 0;
}