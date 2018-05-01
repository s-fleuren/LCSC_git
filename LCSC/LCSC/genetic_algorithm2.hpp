#pragma once

#include <functional>
#include <vector>

namespace lcsc {
	class genetic_algorithm {
	public:
		genetic_algorithm(std::function<double(int)> & objective_function);

		//Selection functions:

		//Recombination functions:

		//Mutation functions:
		int mutation_identity(int chromosome);
		int mutation_test(int chromosome, int p);

		//Stopping criteria:

		//Types of pointers to member functions
		typedef int (lcsc::genetic_algorithm::*MutFn)(int chromosome);
		typedef int (lcsc::genetic_algorithm::*MutFnP)(int chromosome, int p);

		//Functions for deciding which methods to use in the genetic algorithm
		void configure_mutation_function(MutFn fptr);
		void configure_mutation_function(MutFnP fptr, int p);


		std::function<int(int)> mutation_function;

	private:
		std::function<double(int)> & objective_function_;

	};
}