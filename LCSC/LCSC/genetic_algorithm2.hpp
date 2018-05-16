#pragma once

#include <functional>
#include <vector>
#include <memory>

namespace lcsc {
	class genetic_algorithm{
	public:
		genetic_algorithm(std::function<double(double)>& fitness_function, rng_engine & engine, std::vector<chromosome*>& chromosomes, 
			std::vector<chromosome*>& chromosomes2, double recombination_chance, int elitism);

		//Helper functions:
		double compute_total_fitness();
		chromosome* best_chromosome();

		//Selection functions:
		int selection_roulette();

		//Mutation functions:
		int mutation_identity(int chromosome);
		int mutation_test(int chromosome, int p);

		//Main functions:
		void next_generation();
		chromosome* run_ga_iterations(int n);

		//Types of pointers to member functions
		typedef int (lcsc::genetic_algorithm::*MutFn)(int chromosome);
		typedef int (lcsc::genetic_algorithm::*MutFnP)(int chromosome, int p);

		//Functions for deciding which methods to use in the genetic algorithm
		void configure_mutation_function(MutFn fptr);
		void configure_mutation_function(MutFnP fptr, int p);


		std::function<int(int)> mutation_function;

	private:
		std::function<double(double)>& fitness_function_;
		rng_engine& engine_;
		std::vector<chromosome*>& chromosomes_;
		std::vector<chromosome*>& chromosomes2_;
		int generation_no_;
		int generation_size_;
		double recombination_chance_;
		int elitism_;
	};
}