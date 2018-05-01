#include "stdafx.h"
#include "genetic_algorithm2.hpp"

lcsc::genetic_algorithm::genetic_algorithm(std::function<double(int)>& objective_function) :
	objective_function_(objective_function)
	{
		mutation_function = [&](int n) -> int { return n; };
	}

int lcsc::genetic_algorithm::mutation_identity(int chromosome)
{
	return chromosome;
}

int lcsc::genetic_algorithm::mutation_test(int chromosome, int p)
{
	return chromosome + p;
}

void lcsc::genetic_algorithm::configure_mutation_function(MutFn fptr)
{
	mutation_function = [this, fptr](int chromosome) -> 
		int { return (this->*fptr)(chromosome); };
}

void lcsc::genetic_algorithm::configure_mutation_function(MutFnP fptr, int p)
{
	mutation_function = [this, fptr, p](int chromosome) -> 
		int { return (this->*fptr)(chromosome, p); };
}
