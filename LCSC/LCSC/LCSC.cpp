// LCSC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main() {
	uint64_t seed = 6687687898798678888;
	auto engine = lcsc::lcrng(16807, 0, ((1 << 31) - 1), seed);
	auto distrubution = lcsc::uniform_int_distribution(engine, 0, 5);
	auto histogram = lcsc::histogram(engine, 10);
	histogram.test(1000);

	uint32_t seed2 = 5677823;
	auto engine2 = lcsc::xorshift(seed2);
	auto distrubution2 = lcsc::uniform_int_distribution(engine2, 0, 5);
	auto histogram2 = lcsc::histogram(engine2, 10);
	histogram2.test(1000);

}

