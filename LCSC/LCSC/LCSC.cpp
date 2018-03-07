// LCSC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main() {
	srand(time(NULL));
	uint64_t seed = rand();//only two bytes long
	auto engine = lcsc::park_miller(seed);
	uint64_t a = ((uint64_t)1 << 40) - 1;
	uint64_t m = ((uint64_t)1 << 40) - 1;
	auto engine2 = lcsc::lcrng(a, 0, m, seed);
	auto gaussian = lcsc::normal_distribution(engine, 0, 1);
	for (int i = 0; i < 100; i++)
	{
		std::cout << gaussian.sample() << "\n";
	}
	m = (1 << 31) - 1;
	a = 16807;
	std::cout << m % a << "\n";
	std::cout << m / a << "\n";
	printf("Press any key to exit");
	getchar();
}

