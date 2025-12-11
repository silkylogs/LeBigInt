#include "lebigint.h"
#include "Prober/prober.h"

#include <string.h>
#include <stdio.h>

static bool test_lbi_from_int(void) {
	struct LeBigInt expected, got;
	bool result;

	expected.magnitude = "0987654321";
	expected.magnitude_sz = (sizeof "0987654321");
	expected.magnitude_cap = (sizeof "0987654321");
	expected.is_nan = false;
	expected.is_neg = true;

	got = lbi_from_int(-1234567890);

	printf("magnitude:\tExpected: %s,\tGot: %s\n", expected.magnitude, got.magnitude);
	printf("magnitude_sz:\tExpected: %llu,\tGot: %llu\n", expected.magnitude_sz, got.magnitude_sz);
	printf("is_nan:\tExpected: %d,\tGot: %d\n", expected.is_nan, got.is_nan);
	printf("is_neg:\tExpected: %d,\tGot: %d\n", expected.is_neg, got.is_neg);

	result =
		0 == memcmp(expected.magnitude, got.magnitude, got.magnitude_sz)
		&& expected.magnitude_sz == got.magnitude_sz
		&& expected.is_nan == got.is_nan
		&& expected.is_neg == got.is_neg;

	lbi_drop(got);

	return result;
}

int main(void) {
	PROBER_ADD_TEST(test_lbi_from_int);
	PROBER_RUN_TESTS();
	return 0;
}