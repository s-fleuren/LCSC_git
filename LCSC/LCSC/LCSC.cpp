// LCSC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <fstream>
#include <random>
#include <vector>
#include <functional>
#include <time.h>

int main(){
	std::function<double(int)> objective_function = [&](int n) -> double { return n - 1.0; };
	auto ga = lcsc::genetic_algorithm(objective_function);
	int n = 5;
	std::cout << ga.mutation_function(n) << '\n';
	int (lcsc::genetic_algorithm::*fptr) (int) = &lcsc::genetic_algorithm::mutation_identity;
	lcsc::genetic_algorithm* p = &ga;
	ga.configure_mutation_function(fptr);
	std::cout << ga.mutation_function(n) << '\n';
	std::cout << "Press any key to exit.\n";
	getchar();
	return 0;
}