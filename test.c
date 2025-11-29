#include "lebigint.h"
#include "lebigint_handle.h"
#include "Prober/prober.h"

static bool succeeding_test(void) {
	return true;
}

int main(void) {
	PROBER_ADD_TEST(succeeding_test);
	PROBER_RUN_TESTS();
	return 0;
}