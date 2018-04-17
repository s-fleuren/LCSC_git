// LCSC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <fstream>
#include <random>
#include <vector>
#include <functional>
#include <time.h>

double function(double x) {
	return sqrt(1 - x * x);
}

double function2(std::vector<double> x)
{
	return 0.5;
}

double sphere(std::vector<double> x)
{
	double sum = 0;
	int d = (int)x.size();
	for (int i = 0; i < d; i++) sum += x[i] * x[i];
	if (sum <= 1) return 1;
	return 0;
}

int main() {
	clock_t start, end;
	float seconds;

	/*Start clocking*/
	start = clock();

	int d = 2;
	//auto primes = lcsc::primeVector(d);
	int n = 10000;
	//auto halton = lcsc::haltonSequence(primes, d, n);
	//std::function<double(int)> fn = halton.haltonDoubleForExtern();
	auto engine = lcsc::xorshift(5657878786);
	auto min = std::vector<double>(d);
	auto max = std::vector<double>(d);
	for (int i = 0; i < d; i++) min[i] = -1, max[i] = 1;
	auto integral = lcsc::multi_dimensional_hit_or_miss_integration(engine, sphere, min, max, 0, 1);
	std::cout << "simple sampling:\n";
	double outcome = integral.integrate(n);
	std::cout << outcome << "\n";
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Estimating the volume took %f seconds to complete\n\n", seconds);
	printf("Press any key to exit");
	getchar();
	return 0;
}

int oldmain2() {
	std::random_device r;
	auto engine = lcsc::xorshift(r());
	int n = 1000000;
	int loops = 10;
	auto f = function;
	auto integration = lcsc::hit_or_miss_integration(engine, function, 0, 1, 0, 1);
	auto integration2 = lcsc::simple_sampling_integration(engine, function, 0, 1);
	std::cout << "hit or miss:\n";
	for (int i = 0; i < 10; i++)
	{
		double outcome = integration.integrate(n);
		std::cout << outcome << "\n";// π/4≈0.78540
	}
	std::cout << "simple sampling:\n";
	for (int i = 0; i < 10; i++)
	{
		double outcome = integration2.integrate(n);
		std::cout << outcome << "\n";// π/4≈0.78540
	}
	printf("Press any key to exit");
	getchar();
	return 0;
}

int oldmain3() {
	std::random_device r;
	auto engine = lcsc::xorshift(r());
	int n = 100000;
	int loops = 10;
	auto f = function2;
	auto min = std::vector<double>(2);
	min[0] = 0, min[1] = 0;
	auto max = std::vector<double>(2);
	max[0] = 2, max[1] = 3;
	auto integration = lcsc::multi_dimensional_hit_or_miss_integration(engine, function2, min, max, 0, 1);
	auto integration2 = lcsc::multi_dimensional_simple_sampling_integration(engine, function2, min, max);
	std::cout << "hit or miss:\n";
	for (int i = 0; i < 10; i++)
	{
		double outcome = integration.integrate(n);
		std::cout << outcome << "\n";
	}
	std::cout << "simple sampling:\n";
	for (int i = 0; i < 10; i++)
	{
		double outcome = integration2.integrate(n);
		std::cout << outcome << "\n";
	}
	printf("Press any key to exit");
	getchar();
	return 0;
}

int random_numbers_to_file() {
	auto fout = std::ofstream("park_miller_generated_numbers.txt");
	srand(time(NULL));
	uint64_t seed = rand(); //only two bytes long
	auto engine = lcsc::park_miller(seed);
	//int n = 51320000; //enough for smallCrush.
	int n = 1000;
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


int nottmain() {
	srand(time(NULL));
	uint64_t seed = rand(); //only two bytes long
	auto engine = lcsc::lcrng(16807, 0, (1 << 31) - 1, seed);
	//int n = 51320000; //enough for smallCrush.
	int n = 1000000000;

	clock_t start, end;
	float seconds;

	/*Start clocking*/
	start = clock();

	for (int i = 0; i < n; i++)
	{
		auto x = engine.next_int(0, (1 << 30) - 1);
	}

	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Generating 1 billion integers took %f seconds to complete\n\n", seconds);

	printf("Press any key to exit");
	getchar();
	return 0;
}




