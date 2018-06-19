// LCSC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <fstream>
#include <random>
#include <vector>
#include <functional>
#include <list>
#include <memory>
#include <numeric>

using namespace lcsc;

int main() {

	std::cout << "Press any key to exit.\n";
	getchar();
	return 0;
}

void experiment() {
	//std::function<double(std::vector<uint64_t>&)> objective_function = [&](std::vector<uint64_t>& n) -> double { return fmax(0.0, (double)(128 - abs((long long)n[1] - 128))); };
	//std::function<double(uint64_t)> objective_function = [&](uint64_t n) -> double { return fmax(0.0, (double)(128 - abs((long long)n - 128))); };

	std::ofstream output_file;
	output_file.open("output.txt");
	output_file << "test\n";
	output_file.close();

	auto g = graph("graph.txt");
	std::vector<int> degree = std::vector<int>(g.size_V);

	std::function<double(std::vector<uint64_t>&)> objective_function1 = std::bind(objective_trivial, std::placeholders::_1, g);
	std::function<double(std::vector<uint64_t>&)> objective_function2 = std::bind(objective_g_degree, std::placeholders::_1, g);
	std::function<double(std::vector<uint64_t>&)> objective_function3 = std::bind(objective_f_degree_W, std::placeholders::_1, g);
	std::function<double(std::vector<uint64_t>&)> objective_function4 = std::bind(objective_g_degree_W, std::placeholders::_1, g, degree);
	std::function<double(double)> fitness_function = [&](double x) -> double { return fmax(x, 0.000000001); };
	auto engine = xorshift(375766732321);

	int n = 40;
	std::vector<std::unique_ptr<bitstring>> bitstrings;
	std::vector<std::unique_ptr<bitstring>> bitstrings2;
	for (int i = 0; i < n; i++)
	{
		bitstrings.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function3, engine, g.size_V,
			std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(0.01)),
			std::unique_ptr<bitstring::recombination_impl>(new bitstring::recombination_impl_uniform())));
		bitstrings2.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function3, engine, g.size_V,
			std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(0.01)),
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
	auto ga = genetic_algorithm(fitness_function, engine, generation_zero, generation_one, 0.5, 10);
	auto best = ga.timed_experiment(std::chrono::seconds(180), std::chrono::seconds(30), "output.txt");
	best->printbits();
	auto best_bitstring = dynamic_cast<bitstring*>(best);
	auto best_bitstring_bits = best_bitstring->bits;
	auto h = graph(best_bitstring->bits, g);
	std::cout << h.size_V << ' ' << h.size_E << '\n';
	std::cout << objective_function1(best_bitstring_bits) << '\n';
	std::cout << objective_function2(best_bitstring_bits) << '\n';
	std::cout << objective_function3(best_bitstring_bits) << '\n';
	std::cout << objective_function4(best_bitstring_bits) << '\n';
	/*std::cout << "\n\n";
	bitstrings.clear();
	bitstrings2.clear();
	bitstrings.push_back(std::make_unique<bitstring>(best_bitstring_bits, objective_function4, engine, g.size_V,
		std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(0.001)),
		std::unique_ptr<bitstring::recombination_impl>(new bitstring::recombination_impl_uniform())));
	bitstrings2.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function4, engine, g.size_V,
		std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(0.001)),
		std::unique_ptr<bitstring::recombination_impl>(new bitstring::recombination_impl_uniform())));
	for (int i = 1; i < n; i++)
	{
		bitstrings.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function4, engine, g.size_V,
			std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(0.01)),
			std::unique_ptr<bitstring::recombination_impl>(new bitstring::recombination_impl_uniform())));
		bitstrings2.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function4, engine, g.size_V,
			std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(0.01)),
			std::unique_ptr<bitstring::recombination_impl>(new bitstring::recombination_impl_uniform())));
	}
	bitstrings[0]->printbits();
	generation_zero.clear();
	generation_one.clear();
	for (auto& x : bitstrings)
	{
		generation_zero.push_back(x.get());
	}
	for (auto& x : bitstrings2)
	{
		generation_one.push_back(x.get());
	}
	best = ga.run_ga_iterations(1000);
	best->printbits();
	best_bitstring = dynamic_cast<bitstring*>(best);
	h = graph(best_bitstring->bits, g);
	std::cout << h.size_V << ' ' << h.size_E << '\n';*/
}