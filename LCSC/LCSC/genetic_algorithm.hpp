#pragma once

//#include <functional>
#include <vector>
#include <cstdint>
#include <utility>


namespace lcsc {

	template <typename T>
	using objective_fn = std::function<double(bitstring<T>)>;
	
	template <typename T>
	using mutation_fn = std::function<bitstring<T>(bitstring<T>)>;

	template <typename T>
	using selection_fn = std::function<std::vector<std::pair<bitstring<T>, bitstring<T>>>
		(std::vector<bitstring<T>>)>;

	template <typename T>
	using recombination_fn = std::function<std::pair<bitstring<T>, bitstring<T>>
		(std::pair<bitstring<T>, bitstring<T>>)>;
	
	template <typename T>
	class genetic_algorithm {
	public:
		genetic_algorithm(rng_engine & engine, objective_fn & objective_function);
		bitstring<T> start(std::vector<bitstring<T>> current_generation);
	
	private:
		rng_engine & engine_;
		std::vector<bitstring<T>> population_;
		objective_fn & objective_function_;
		mutation_fn & mutation_function_;
		selection_fn & selection_function_;
		uint64_t no_selected_parents_;
		recombination_fn & recombination_function_;
	};

	template<typename T>
	inline genetic_algorithm<T>::genetic_algorithm(rng_engine & engine, objective_fn & objective_function) :
		engine_(engine), objective_function_(objective_function)
	{
		mutation_function_ = [&](bitstring<T> chromosome) -> bitstring<T> { return chromosome; };
		selection_function_ = [&](std::pair<bitstring<T>, bitstring<T>> parents)
			std::pair<bitstring<T>, bitstring<T>> { return parents; };

	}

	template<typename T>
	inline bitstring<T> genetic_algorithm<T>::start(std::vector<bitstring<T>> initial_generation)
	{
		auto population_size = current_generation.size;
		auto next_generation = std::vector<bitstring<T>>(population_size);
		auto pairs = std::vector < std::pair<bitstring<T>, bitstring<T>>(population_size / 2);
		while (not stop_function_())
		{
			pairs = selection_function_(current_generation);
			pairs = recombination_function(pairs);
			for (int i = 0; i < population_size / 2; i++)
			{
				next_generation[2 * i] = mutation_function_(pairs[i].first);
				next_generation[2 * i + 1] = mutation_function_(pairs[i].second);
			}
			current_generation = next_generation;
		}
		auto output = current_generation[0];
		for (int i = 1; i < population_size; i++)
		{
			if objective_function(ouput) < objective_function(current_generation[i])
			{
				output = current_generation[i];
			}
		}
		return output;
	}//*/

} // namespace lcsc