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
	//std::function<double(std::vector<uint64_t>&)> objective_function = [&](std::vector<uint64_t>& n) -> double { return fmax(0.0, (double)(128 - abs((long long)n[1] - 128))); };
	//std::function<double(uint64_t)> objective_function = [&](uint64_t n) -> double { return fmax(0.0, (double)(128 - abs((long long)n - 128))); };
	
	auto g = graph("graph.txt");
	std::cout << g.vertex_dict["1"] << '\n';
	std::cout << g.vertex_dict["2"] << '\n';
	std::cout << g.vertex_dict["3"] << '\n';
	std::cout << g.vertex_dict["4"] << '\n';
	std::cout << '\n' << g.size_V << '\n';
	for (int i = 0; i < g.size_V; i++)
	{
		std::cout << "\n";
		for (auto a : *g.neighbours[i])
		{
			std::cout << a << ' ';
		}
	}
	std::cout << "\n";

	std::function<double(std::vector<uint64_t>&)> objective_function = [&](std::vector<uint64_t>& n) -> double { 
		double sum = 0;
		size_t vertex;
		uint64_t neighbour_inner, neighbour_outer;
		bool has_edge;
		for (int outer = 0; outer < (g.size_V >> 6); outer++)
		{
			for (int inner = 0; inner < 64; inner++)
			{
				vertex = 64 * outer + inner;
				if ((n[outer] & ((uint64_t)1 << inner)) != 0)
				{
					has_edge = false;
					for (auto neighbour : *g.neighbours[vertex])
					{
						neighbour_inner = neighbour % 64;
						neighbour_outer = (neighbour >> 6);
						if ((n[neighbour_outer] & ((uint64_t)1 << neighbour_inner)) != 0)
						{
							has_edge = true;
							break;
						}
					}
					if (!has_edge) sum += 1;
				}
			}
		}
		for (int inner = 0; inner < g.size_V % 64; inner++)
		{
			vertex = inner;
			if ((n.back() & ((uint64_t)1 << inner)) != 0)
			{
				has_edge = false;
				for (auto neighbour : *g.neighbours[vertex])
				{
					neighbour_inner = neighbour % 64;
					neighbour_outer = (neighbour >> 6);
					if ((n[neighbour_outer] & ((uint64_t)1 << neighbour_inner)) != 0)
					{
						has_edge = true;
						break;
					}
				}
				if (!has_edge) sum += 1;
			}
		}
		return sum;
	};
	std::function<double(double)> fitness_function = [&](double x) -> double { return fmax(x, 0.000000001); };
	auto engine = xorshift(675766732321);

	int n = 20;
	std::vector<std::unique_ptr<bitstring>> bitstrings;
	std::vector<std::unique_ptr<bitstring>> bitstrings2;
	for (int i = 0; i < n; i++)
	{
		bitstrings.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function, engine, g.size_V,
			std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(0.1)),
			std::unique_ptr<bitstring::recombination_impl>(new bitstring::recombination_impl_uniform())));
		bitstrings2.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function, engine, g.size_V,
			std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(0.1)),
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
	auto ga = genetic_algorithm(fitness_function, engine, generation_zero, generation_one, 0.5, 4);
	chromosome* best = ga.run_ga_iterations(1000);
	std::cout << "Press any key to exit.\n";
	getchar();

	return 0;
}