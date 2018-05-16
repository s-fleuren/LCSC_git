#include "stdafx.h"
#include <algorithm>

using namespace lcsc;

genetic_algorithm::genetic_algorithm(std::function<double(double)>& fitness_function, rng_engine & engine, 
	std::vector<chromosome*>& chromosomes, std::vector<chromosome*>& chromosomes2, double recombination_chance, int elitism) :
	fitness_function_(fitness_function), engine_(engine), chromosomes_(chromosomes), chromosomes2_(chromosomes2)
	{
		mutation_function = [&](int n) -> int { return n; };
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
		if (chromosomes_[i]->selected == false)
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
	int best_fitness = 0;
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
		if (chromosomes_[i]->selected == false)
		{
			sum += fitness_function_(chromosomes_[i]->objective_value());
			if (sum > S)
			{
				chromosomes_[i]->selected = 1;
				return i;
			}
		}
	}
	std::cout << "selection failed";
}

int genetic_algorithm::mutation_identity(int chromosome)
{
	return chromosome;
}

int genetic_algorithm::mutation_test(int chromosome, int p)
{
	return chromosome + p;
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
			if (selected_index >= elitism_)
			{
				chromosomes2_[index]->clone(chromosomes_[selected_index]);
				index++;
			}
			if (engine_.next_double() < recombination_chance_)
			{
				parents[p] = chromosomes_[selected_index];
				p++;
			}
		}
		if (index < generation_size_)
		{
			parents[0]->recombine(parents[1], 10);
			p = 0;
			chromosomes2_[index]->clone(parents[0]);
			index++;
			if (index < generation_size_)
			{
				chromosomes2_[index]->clone(parents[1]);
				index++;
			}
		}
	}
	for (int i = elitism_; i < generation_size_; i++)
	{
		chromosomes2_[i]->mutate(0.5);
		std::swap(chromosomes_[i], chromosomes2_[i]);
	}
	std::partial_sort(chromosomes_.begin(), chromosomes_.begin() + elitism_, chromosomes_.end(),
		[&](auto lhs, auto rhs) {return lhs->objective_value() > rhs->objective_value(); });
}

chromosome* genetic_algorithm::run_ga_iterations(int n)
{
	for (int i = 0; i < n; i++)
	{
		next_generation();
		chromosomes_[0]->printbits();
	}
	return best_chromosome();
}

void genetic_algorithm::configure_mutation_function(MutFn fptr)
{
	mutation_function = [this, fptr](int chromosome) -> 
		int { return (this->*fptr)(chromosome); };
}

void genetic_algorithm::configure_mutation_function(MutFnP fptr, int p)
{
	mutation_function = [this, fptr, p](int chromosome) -> 
		int { return (this->*fptr)(chromosome, p); };
}
