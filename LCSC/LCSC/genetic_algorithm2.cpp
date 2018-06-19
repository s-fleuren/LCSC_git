#include "stdafx.h"
#include <algorithm>
#include <chrono>

using namespace lcsc;

genetic_algorithm::genetic_algorithm(std::function<double(double)>& fitness_function, rng_engine & engine, 
	std::vector<chromosome*>& chromosomes, std::vector<chromosome*>& chromosomes2, double recombination_chance, int elitism) :
	fitness_function_(fitness_function), engine_(engine), chromosomes_(chromosomes), chromosomes2_(chromosomes2)
	{
		generation_no_ = 0;
		generation_size_ = chromosomes.size();
		recombination_chance_ = recombination_chance;
		elitism_ = elitism;

		std::partial_sort(chromosomes_.begin(), chromosomes_.begin() + elitism_, chromosomes_.end(),
			[&](auto lhs, auto rhs) {return lhs->objective_value() > rhs->objective_value(); });
	}

double genetic_algorithm::compute_total_fitness()
{
	double output = 0;
	for(int i = 0; i < generation_size_; i++)
	{
		if (chromosomes_[i]->selected_ == false)
		{
			output += fitness_function_(chromosomes_[i]->objective_value());
		}
	}
	return output;
}

chromosome* genetic_algorithm::best_chromosome()
{
	if (elitism_ > 0)
	{
		return chromosomes_[0];
	}
	double best_fitness = 0;
	chromosome* output = nullptr;
	for (int i = 0; i < generation_size_; i++)
	{
		if (fitness_function_(chromosomes_[i]->objective_value()) > best_fitness)
		{
			best_fitness = fitness_function_(chromosomes_[i]->objective_value());
			output = chromosomes_[i];
		}
	}
	std::cout << best_fitness << "\n";
	output->printbits();
	return output;
}

int genetic_algorithm::selection_roulette()
{
	double T = compute_total_fitness();
	double S = engine_.next_double(0, T);
	double sum = 0;
	for (int i = 0; i < generation_size_; i++)
	{
		if (chromosomes_[i]->selected_ == false)
		{
			sum += fitness_function_(chromosomes_[i]->objective_value());
			if (sum > S)
			{
				chromosomes_[i]->selected_ = 1;
				return i;
			}
		}
	}
	std::cout << "selection failed";
	exit(1);
}

void genetic_algorithm::next_generation()
{
	int p = 0;
	int index = elitism_;
	int selected_index;
	auto parents = std::vector<chromosome*>(2);
	while (index < generation_size_)
	{
		while (p < 2 and index < generation_size_)
		{
			selected_index = selection_roulette();
			if (engine_.next_double() < recombination_chance_)
			{
				parents[p] = chromosomes_[selected_index];
				p++;
			}
			if (selected_index >= elitism_)
			{
				chromosomes2_[index]->clone(chromosomes_[selected_index]);
				index++;
			}
		}
		if (index < generation_size_)
		{
			chromosomes2_[index]->clone(parents[0]);
			index++;
			if (index < generation_size_)
			{
				chromosomes2_[index]->clone(parents[1]);
				chromosomes2_[index - 1]->recombine(chromosomes2_[index]);
				index++;
			}
			else
			{
				chromosomes_.back()->clone(parents[1]);
				chromosomes2_[index - 1]->recombine(chromosomes_.back());
			}
			p = 0;
		}
	}
	for (int i = elitism_; i < generation_size_; i++)
	{
		chromosomes2_[i]->mutate();
		std::swap(chromosomes_[i], chromosomes2_[i]);
	}
	std::partial_sort(chromosomes_.begin(), chromosomes_.begin() + elitism_, chromosomes_.end(),
		[&](auto lhs, auto rhs) {return lhs->objective_value() > rhs->objective_value(); });
	for (int i = 0; i < generation_size_; i++)
	{
		chromosomes_[i]->selected_ = false;
	}
	generation_no_++;
}

chromosome* genetic_algorithm::run_ga_iterations(int n)
{
	for (int i = 0; i < n; i++)
	{
		next_generation();
		//chromosomes_[0]->printbits();
		//std::cout << (chromosomes_[0]->objective_value()) << "\n";
	}
	return best_chromosome();
}

chromosome * lcsc::genetic_algorithm::timed_experiment(std::chrono::seconds duration, std::chrono::seconds sample_moment, 
	std::string filename)
{
	std::ofstream output_file;
	output_file.open(filename, std::ios_base::app);
	auto start = std::chrono::steady_clock::now();
	auto sample = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < duration)
	{
		sample = std::chrono::steady_clock::now();
		std::chrono::duration<double> delta = sample - start;
		output_file << delta.count() << ' ' << (chromosomes_[0]->objective_value()) << ' ' 
			<< generation_no_ << '\n';
		while (std::chrono::steady_clock::now() - sample < sample_moment)
		{
			next_generation();
		}
	}
	while (std::chrono::steady_clock::now() - sample < sample_moment)
	{
		next_generation();
	}
	sample = std::chrono::steady_clock::now();
	std::chrono::duration<double> delta = sample - start;
	output_file << delta.count() << ' ' << (chromosomes_[0]->objective_value()) << ' '
		<< generation_no_ << '\n';
	output_file.close();
	return chromosomes_[0];
}
