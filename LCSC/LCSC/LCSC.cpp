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

using namespace lcsc;

int main(){
	std::function<double(uint64_t)> objective_function = [&](int n) -> double { return n - 1.0; };
	auto engine = xorshift(675667675);
	int n = 4;
	std::vector<std::unique_ptr<bitstring64>> bitstrings;
	for (int i = 0; i < n; i++)
	{
		bitstrings.push_back(std::make_unique<bitstring64>(objective_function, engine));
	}
	std::vector<chromosome*> generation_zero;
	for (auto& x : bitstrings)
	{
		generation_zero.push_back(x.get());
	}
	for (int i = 0; i < n; i++)
	{
		generation_zero[i]->printbits();
	}
	std::cout << "\n";
	for (int i = 0; i < n; i++)
	{
		generation_zero[i]->mutate(1);
		generation_zero[i]->printbits();
	}
	std::cout << "\n";
	/*for (int i = 0; i < n; i += 2)
	{
		generation_zero[i]->recombine(generation_zero[i + 1]);
		generation_zero[i]->printbits();
		generation_zero[i + 1]->printbits();
	}*/
	auto ga = genetic_algorithm(objective_function, engine, generation_zero);
	std::cout << "Press any key to exit.\n";
	getchar();
	return 0;
}