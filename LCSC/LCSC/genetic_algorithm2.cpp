#include "stdafx.h"
#include "genetic_algorithm2.hpp"

lcsc::genetic_algorithm::genetic_algorithm(std::function<double(int)>& objective_function) :
	objective_function_(objective_function)
	{
		mutation_function = [&](int n) -> int { 
			std::cout << "Warning: mutation function has not been configured. No mutation will take place.\n";
			return n; };
	}

int lcsc::genetic_algorithm::mutation_identity(int chromosome)
{
	return chromosome;
}

void lcsc::genetic_algorithm::configure_mutation_function(int (lcsc::genetic_algorithm::*fptr) (int))
{
	mutation_function = [this, fptr](int n) -> int { return (this->*fptr)(n); };
}
