// LCSC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main() {
	uint64_t seed = 6687687898798678888;
	auto engine = lcsc::lcrng(16807, 0, ((1 << 31) - 1), seed);
	auto distrubution = lcsc::uniform_int_distribution(engine, 0, 5);
	auto histogram = lcsc::histogram(engine, 10);
	histogram.test(1000);
}

