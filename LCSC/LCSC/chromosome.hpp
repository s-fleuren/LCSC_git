#pragma once

#include <cstdint>
#include <utility>

namespace lcsc {

	class chromosome {
	public:
		virtual double objective_value() = 0;
		virtual void printbits() = 0;
		virtual void mutate(double p) = 0;

	protected:
		friend class genetic_algorithm;
		virtual void clone(chromosome* other) = 0;
		virtual std::pair<chromosome, chromosome> recombine(chromosome* partner, int crossover_point) = 0;

		bool selected;
	};

	class bitstring64 : public chromosome {
	public:
		bitstring64(uint64_t genotype, std::function<double(uint64_t)> & objective_function, rng_engine & engine, const int length);
		bitstring64(std::function<double(uint64_t)> & objective_function, rng_engine & engine, const int length);
		double objective_value() override;
		void printbits() override;
		void mutate(double p) override;

		//copy constructors
		//bitstring64(const bitstring64& other) : 
		//	objective_function_(other.objective_function_), engine_(other.engine_), bits(other.bits) {}
		bitstring64& operator=(const bitstring64& other)
		{
			objective_function_ = other.objective_function_;
			engine_ = other.engine_;
			bits = other.bits;
			length_ = other.length_;
			selected = other.selected;
			return *this;
		}

		uint64_t bits;

	private:
		friend class genetic_algorithm;
		std::pair<chromosome, chromosome> recombine(chromosome* partner, int crossover_point) override;
		void clone(chromosome* other) override;

		std::function<double(uint64_t)>& objective_function_;
		rng_engine& engine_;
		int length_;
	};
}