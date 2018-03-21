// LCSC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>

double function(double x) {
	return sqrt(1-x*x);
}

int main() {
	srand(time(NULL));
	uint64_t seed = rand();//only two bytes long
	auto engine = lcsc::xorshift(seed);
	int n = 10000;
	auto f = function;
	auto integration = lcsc::hit_or_miss_integration(engine, function);
	double outcome = integration.integrate(n);
	for (int i = 0; i < 100; i++)
	{
		std::cout << engine.next_normal(0, 1) << "\n";
	}
	std::cout << outcome << "\n";
	printf("Press any key to exit");
	getchar();
}

