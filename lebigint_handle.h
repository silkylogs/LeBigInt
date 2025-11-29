#ifndef LE_BIG_INT_HANDLE_2025_11_29_H
#define LE_BIG_INT_HANDLE_2025_11_29_H

struct LeBigInt {
	char *magnitude;
	size_t magnitude_cnt;
	bool is_nan;
	bool is_neg;
};

#endif