#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <chrono>

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

		//Main functions:
		void next_generation();
		chromosome* run_ga_iterations(int n);
		chromosome* timed_experiment(std::chrono::seconds duration, std::chrono::seconds sample_moment, std::string filename);

	private:
		std::function<double(double)>& fitness_function_;
		rng_engine& engine_;
		std::vector<chromosome*>& chromosomes_;
		std::vector<chromosome*>& chromosomes2_;
		int generation_no_;
		size_t generation_size_;
		double recombination_chance_;
		int elitism_;
	};
}