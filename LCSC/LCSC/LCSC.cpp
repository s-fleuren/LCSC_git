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

int main() {
	//std::function<double(std::vector<uint64_t>&)> objective_function = [&](std::vector<uint64_t>& n) -> double { return fmax(0.0, (double)(128 - abs((long long)n[1] - 128))); };
	//std::function<double(uint64_t)> objective_function = [&](uint64_t n) -> double { return fmax(0.0, (double)(128 - abs((long long)n - 128))); };

	auto g = graph("graph.txt");

	std::function<double(std::vector<uint64_t>&)> objective_function = [&](std::vector<uint64_t>& n) -> double {
		double sum = 0;
		uint64_t bits;
		size_t inner, outer, value;
		std::vector<size_t> degree = std::vector<size_t>(g.size_V);
		for (int vertex = 0; vertex < g.size_V; vertex++)
		{
			inner = vertex % 64;
			outer = (vertex >> 6);
			if ((n[outer] & ((uint64_t)1 << inner)) != 0)
			{
				degree[vertex] = 0;
				for (int i = 0; i < g.neighbours_outer[vertex]->size(); i++)
				{
					bits = n[g.neighbours_outer[vertex]->at(i)] & g.neighbours_bits[vertex]->at(i);
					for (int j = 0; j < 64; j++)
					{
						degree[vertex] += bits % 2;
						bits >>= 1;
					}
				}
			}
		}
		for (int u = 0; u < g.size_V; u++)
		{
			inner = u % 64;
			outer = (u >> 6);
			if ((n[outer] & ((uint64_t)1 << inner)) != 0)
			{
				value = degree[u];
				for (auto v : *g.neighbours[u])
				{
					if (degree[v] != 0 && degree[v] <= degree[u] && degree[v] > value)
					{
						value = degree[v];
					}
				}
				sum += (double)1 / (value + 1);
			}
		}
		return sum;
	};
	std::function<double(double)> fitness_function = [&](double x) -> double { return fmax(x, 0.000000001); };
	auto engine = xorshift(675766732321);

	int n = 40;
	std::vector<std::unique_ptr<bitstring>> bitstrings;
	std::vector<std::unique_ptr<bitstring>> bitstrings2;
	for (int i = 0; i < n; i++)
	{
		bitstrings.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function, engine, g.size_V,
			std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(0.001)),
			std::unique_ptr<bitstring::recombination_impl>(new bitstring::recombination_impl_uniform())));
		bitstrings2.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function, engine, g.size_V,
			std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(0.001)),
			std::unique_ptr<bitstring::recombination_impl>(new bitstring::recombination_impl_uniform())));
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
	auto ga = genetic_algorithm(fitness_function, engine, generation_zero, generation_one, 1, 10);
	chromosome* best = ga.run_ga_iterations(10000);
	best->printbits();
	auto best_bitstring = dynamic_cast<bitstring*>(best);
	auto h = graph(best_bitstring->bits, g);
	std::cout << h.size_V << ' ' << h.size_E << '\n';
	std::cout << "Press any key to exit.\n";
	getchar();
	return 0;
}