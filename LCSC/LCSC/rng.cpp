#include "stdafx.h"

namespace lcsc {

	double lcrng::next() {
		x_ = (a_*x_ + c_) % m_;
		return x_ / (m_ - 1.0);
	}

	uint64_t lcrng::next_int(uint64_t min, uint64_t max) {
		return 0;//TODO
	}

	uint64_t xorshift::next_int(uint64_t min = 0, uint64_t max = (1 << 63) - 1) {
		if (min > max)
		{
			printf("Error: value of min is greater than the value of max. Press enter to exit");
			getchar();
			exit(1);
		}
		uint64_t i = max - min;
		if (i != (1 << 63) - 1)
		{
			i |= (i >> 1);
			i |= (i >> 2);
			i |= (i >> 4);
			i |= (i >> 8);
			i |= (i >> 16);
			i |= (i >> 32);
			i -= (i >> 1);
		}
		else (i = 0);

		while (1 > 0)
		{
			x_ ^= x_ >> 12;
			x_ ^= x_ << 25;
			x_ ^= x_ >> 27;
			uint64_t output = (x_ >> i) + min;
			if (output <= max) return output;
		}
	}

	double xorshift::next() {
		uint64_t x = next_int();
		uint64_t m = ((1 << 63) - 1);
		return (double)x / m;
	}

} // namespace lcsc
