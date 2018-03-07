#include "stdafx.h"
#include <intrin.h>
#include <math.h>

namespace lcsc {

	double lcrng::next_double() {
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
		uint64_t range = max - min;
		if (range >= m_)
		{
			printf("Error: range is too large. Press any key to exit.");
			getchar();
			exit(1);
		}
		if (range == m_ - 1)
		{
			x_ = (a_*x_ + c_) % m_;
			return x_;
		}
		return (uint64_t)(next_double()*range + min);
	}

	uint64_t park_miller::next_int(uint64_t min = 0, uint64_t max = (1 << 31) - 2) {
		if (min > max)
		{
			printf("Error: value of min is greater than the value of max. Press enter to exit.");
			getchar();
			exit(1);
		}
		uint64_t range = max - min;
		if (range >= m_)
		{
			printf("Error: range is too large. Press any key to exit.");
			getchar();
			exit(1);
		}
		if (range == m_ - 1)
		{
			x_ = (a_ * (x_ % q_) - r_ * (x_ / q_) + m_) % m_;//Schrage’s trick
			return x_ + min;
		}
		unsigned long index;
		_BitScanReverse64(&index, range);//2**index <= range < 2**(index+1)
		while (1 > 0)
		{
			x_ = (a_ * (x_ % q_) - r_ * (x_ / q_) + m_) % m_;
			uint64_t output = (x_ >> (63 - index)) + min;
			if (output <= max) return output;
		}
	}

	double park_miller::next_double() {
		uint64_t x = next_int();
		return (double)x / m_;
	}

	uint64_t xorshift::next_int(uint64_t min = 0, uint64_t max = ((uint64_t)1 << 63) - 1) {
		if (min > max)
		{
			printf("Error: value of min is greater than the value of max. Press enter to exit.");
			getchar();
			exit(1);
		}
		uint64_t range = max - min;
		if (range == ((uint64_t)1 << 63) - 1)
		{
			x_ ^= x_ >> 12;
			x_ ^= x_ << 25;
			x_ ^= x_ >> 27;
			return x_;
		}
		unsigned long index;
		_BitScanReverse64(&index, range);//2**index <= range < 2**(index+1)
		while (1 > 0)
		{
			x_ ^= x_ >> 12;
			x_ ^= x_ << 25;
			x_ ^= x_ >> 27;
			uint64_t output = (x_ >> (63 - index)) + min;
			if (output <= max) return output;
		}
	}

	double xorshift::next_double() {
		uint64_t x = next_int();
		uint64_t m = (((uint64_t)1 << 63) - 1);
		return (double)x / m;
	}

} // namespace lcsc
