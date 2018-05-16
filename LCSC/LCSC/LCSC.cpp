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
	std::function<double(uint64_t)> objective_function = [&](int n) -> double { return fmax(0.0, (double)(128 - abs(n - 128))); };
	std::function<double(double)> fitness_function = [&](double x) -> double { return fmax(x, 0.000000001); };
	auto engine = xorshift(675766732321);
	
	int n = 20;
	std::vector<std::unique_ptr<bitstring64>> bitstrings;
	std::vector<std::unique_ptr<bitstring64>> bitstrings2;
	for (int i = 0; i < n; i++)
	{
		bitstrings.push_back(std::make_unique<bitstring64>(objective_function, engine, 10));
		bitstrings2.push_back(std::make_unique<bitstring64>(0, objective_function, engine, 10));
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
	chromosome* best = ga.run_ga_iterations(100);
	std::cout << "Press any key to exit.\n";
	getchar();
	return 0;
}