#pragma once

#include <functional>
#include <vector>

namespace lcsc {
	class genetic_algorithm {
	public:
		typedef int (lcsc::genetic_algorithm::*MutFn)(int chromosome);
		genetic_algorithm(std::function<double(int)> & objective_function);

		//Mutation functions:
		int mutation_identity(int chromosome);

		//Functions for deciding which methods to use in the genetic algorithm
		void configure_mutation_function(int (lcsc::genetic_algorithm::*fptr) (int));


		std::function<int(int)> mutation_function;

	private:
		std::function<double(int)> & objective_function_;

	};
}