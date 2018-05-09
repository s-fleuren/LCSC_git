#include "stdafx.h"
#include "genetic_algorithm2.hpp"

using namespace lcsc;

genetic_algorithm::genetic_algorithm(std::function<double(double)>& fitness_function, rng_engine & engine, std::vector<chromosome*> chromosomes) :
	fitness_function_(fitness_function), engine_(engine), chromosomes_(chromosomes)
	{
		mutation_function = [&](int n) -> int { return n; };
		generation_size_ = chromosomes.size;
	}

double lcsc::genetic_algorithm::compute_total_fitness()
{
	double output = 0;
	for(auto x : chromosomes_)
	{
		output += fitness_function_(x->objective_value());
	}
	return output;
}

void genetic_algorithm::selection_roulette()
{
	double T = compute_total_fitness();

}

int genetic_algorithm::mutation_identity(int chromosome)
{
	return chromosome;
}

int genetic_algorithm::mutation_test(int chromosome, int p)
{
	return chromosome + p;
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
