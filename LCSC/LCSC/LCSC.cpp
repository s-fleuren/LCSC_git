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

void experiment(std::string graphfile, std::string outputfile, std::string outputfileplot, int fn_number,
	int m, double p_m, rng_engine& engine) {
	//std::function<double(std::vector<uint64_t>&)> objective_function = [&](std::vector<uint64_t>& n) -> double { return fmax(0.0, (double)(128 - abs((long long)n[1] - 128))); };
	//std::function<double(uint64_t)> objective_function = [&](uint64_t n) -> double { return fmax(0.0, (double)(128 - abs((long long)n - 128))); };

	std::ofstream output_file;
	output_file.open(outputfile, std::ios_base::app);

	auto g = graph(graphfile);
	std::vector<int> degree = std::vector<int>(g.size_V);

	std::function<double(std::vector<uint64_t>&)> objective_function;
	if (fn_number == 1)
	{
		objective_function = std::bind(objective_trivial, std::placeholders::_1, g);
	}
	if (fn_number == 2)
	{
		objective_function = std::bind(objective_g_degree, std::placeholders::_1, g);
	}
	if (fn_number == 3)
	{
		objective_function = std::bind(objective_f_degree_W, std::placeholders::_1, g);
	}
	if (fn_number == 4)
	{
		objective_function = std::bind(objective_g_degree_W, std::placeholders::_1, g, degree);
	}
	double minimum = objective_function(g.bits);
	std::function<double(double)> fitness_function = [&](double x) -> double { return fmax(x - minimum, 0.000001); };

	std::vector<std::unique_ptr<bitstring>> bitstrings;
	std::vector<std::unique_ptr<bitstring>> bitstrings2;
	for (int i = 0; i < m; i++)
	{
		bitstrings.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function, engine, g.size_V,
			std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(p_m)),
			std::unique_ptr<bitstring::recombination_impl>(new bitstring::recombination_impl_uniform())));
		bitstrings2.push_back(std::make_unique<bitstring>(random_bits_vector(g.size_V, engine), objective_function, engine, g.size_V,
			std::unique_ptr<bitstring::mutation_impl>(new bitstring::mutation_impl_uniform(p_m)),
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
	auto ga = genetic_algorithm(fitness_function, engine, generation_zero, generation_one, 0.5, m / 5);
	auto best = ga.timed_experiment(std::chrono::seconds(600), std::chrono::seconds(60), outputfileplot);
	auto best_bitstring = dynamic_cast<bitstring*>(best);
	auto best_bitstring_bits = best_bitstring->bits;
	auto h = graph(best_bitstring->bits, g);
	output_file << objective_function(best_bitstring_bits) << " & " << h.size_V << " & " << h.size_E << 
		" & "  << ga.generation_no / 10 << "\\\\\n";
	output_file.close();
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

int main() {
	auto engine = xorshift(375766732321);
	for (int i = 1; i <= 4; i++)
	{
		std::string graphfile = "graph" + std::to_string(i) + ".col";
		for (int j = 1; j <= 4; j++)
		{
			std::string outputfileplot = "outputplot00" + std::to_string(i) + ".txt";
			std::string outputfile = "output00" + std::to_string(i) + ".txt";
			experiment(graphfile, outputfile, outputfileplot, j, 20, 0.001, engine);

			outputfileplot = "outputplot01" + std::to_string(i) + ".txt";
			outputfile = "output01" + std::to_string(i) + ".txt";
			experiment(graphfile, outputfile, outputfileplot, j, 80, 0.001, engine);

			outputfileplot = "outputplot10" + std::to_string(i) + ".txt";
			outputfile = "output10" + std::to_string(i) + ".txt";
			experiment(graphfile, outputfile, outputfileplot, j, 20, 0.1, engine);

			outputfileplot = "outputplot11" + std::to_string(i) + ".txt";
			outputfile = "output11" + std::to_string(i) + ".txt";
			experiment(graphfile, outputfile, outputfileplot, j, 80, 0.1, engine);
		}
	}
	std::cout << "Press any key to exit.\n";
	getchar();
	return 0;
}
