#pragma once

#include <functional>
#include <vector>
#include <memory>

namespace lcsc {
	class genetic_algorithm{
	public:
		genetic_algorithm(std::function<double(double)>& fitness_function, rng_engine & engine, std::vector<chromosome*> chromosomes);

		//Helper functions:
		double compute_total_fitness();

		//Selection functions:
		void selection_roulette();

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
		std::function<double(double)> & fitness_function_;
		rng_engine & engine_;
		std::vector<chromosome*> chromosomes_;
		int generation_size_;
	};
}