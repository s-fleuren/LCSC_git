// LCSC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <fstream>
#include <random>
#include <vector>
#include <functional>
#include <time.h>
#include <list>
#include <memory>
#include <numeric>

using namespace lcsc;

int main(){
	std::function<double(std::vector<uint64_t>&)> objective_function = [&](std::vector<uint64_t>& n) -> double { return fmax(0.0, (double)(128 - abs((long long)n[1] - 128))); };
	std::function<double(double)> fitness_function = [&](double x) -> double { return fmax(x, 0.000000001); };
	auto engine = xorshift(675766732321);
	
	int n = 20;
	std::vector<std::unique_ptr<bitstring>> bitstrings;
	std::vector<std::unique_ptr<bitstring>> bitstrings2;
	for (int i = 0; i < n; i++)
	{
		bitstrings.push_back(std::make_unique<bitstring>(random_bits_vector(72, engine), objective_function, engine, 72, 62));
		bitstrings2.push_back(std::make_unique<bitstring>(random_bits_vector(72, engine), objective_function, engine, 72, 62));
	}
	std::vector<chromosome*> generation_zero;
	std::vector<chromosome*> generation_one;
	for (auto& x : bitstrings)
	{
		generation_zero.push_back(x.get());
	}
	for (auto& x : bitstrings2)
	{
		generation_one.push_back(x.get());
	}
	auto ga = genetic_algorithm(fitness_function, engine, generation_zero, generation_one, 0.5, 4);
	//ga.next_generation();
	chromosome* best = ga.run_ga_iterations(1000);
	std::cout << "Press any key to exit.\n";
	getchar();
	return 0;
}