// LCSC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <fstream>

double function(double x) {
	return sqrt(1-x*x);
}

int main() {
	auto fout = std::ofstream("park_miller_generated_numbers.txt");
	srand(time(NULL));
	uint64_t seed = rand(); //only two bytes long
	auto engine = lcsc::park_miller(seed);
	int n = 51320000; //enough for smallCrush.
	//int n = 1000;
	for (int i = 0; i < n; i++)
	{
		auto x = engine.next_double();
		if (x < 1)
		{
			fout << engine.next_double() << "\n";
		}
	}
	printf("Press any key to exit");
	getchar();
	return 0;
}




int oldmain() {
	auto fout = std::ofstream("some_file.txt");
	srand(time(NULL));
	uint64_t seed = rand();//only two bytes long
	auto engine = lcsc::xorshift(seed);
	int n = 10000;
	auto f = function;
	auto integration = lcsc::hit_or_miss_integration(engine, function);
	double outcome = integration.integrate(n);
	for (int i = 0; i < 100; i++)
	{
		fout << engine.next_normal(0, 1) << "\n";
	}
	std::cout << outcome << "\n";
	printf("Press any key to exit");
	getchar();
}

