#include "stdafx.h"
#include <intrin.h>;
#include <math.h>;

namespace lcsc {

	double lcrng::next() {
		x_ = (a_*x_ + c_) % m_;
		return x_ / (m_ - 1.0);
	}

	uint64_t lcrng::next_int(uint64_t min, uint64_t max) {
		if (min > max)
		{
			printf("Error: value of min is greater than the value of max. Press enter to exit.");
			getchar();
			exit(1);
		}
		uint64_t period = max - min;
		if (period >= m_)
		{
			printf("Error: period is too large. Press any key to exit.");
			getchar();
			exit(1);
		}
		unsigned long index;
		_BitScanReverse64(&index, period);//2**i <= period < 2**(i+1)
		while (1 > 0)
		{
			x_ = (a_*x_ + c_) % m_;
			if ((x_ >> index) <= period)
			{
				return min;
			}
		}
	}

	uint64_t xorshift::next_int(uint64_t min = 0, uint64_t max = (1 << 63) - 1) {
		if (min > max)
		{
			printf("Error: value of min is greater than the value of max. Press enter to exit.");
			getchar();
			exit(1);
		}
		uint64_t period = max - min;
		if (period == (1 << 63) - 1)
		{
			x_ ^= x_ >> 12;
			x_ ^= x_ << 25;
			x_ ^= x_ >> 27;
			return x_;
		}
		unsigned long index;
		_BitScanReverse64(&index, period);//2**index <= period < 2**(index+1)
		while (1 > 0)
		{
			x_ ^= x_ >> 12;
			x_ ^= x_ << 25;
			x_ ^= x_ >> 27;
			uint64_t output = (x_ >> (63 - index)) + min;
			if (output <= max) return output;
		}
	}

	double xorshift::next() {
		uint64_t x = next_int();
		uint64_t m = ((1 << 63) - 1);
		return (double)x / m;
	}

} // namespace lcsc
