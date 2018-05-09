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
		virtual void recombine(chromosome* partner) = 0;
	};

	class bitstring64 : public chromosome {
	public:
		bitstring64(uint64_t genotype, std::function<double(uint64_t)> & objective_function, rng_engine & engine);
		bitstring64(std::function<double(uint64_t)> & objective_function, rng_engine & engine);
		double objective_value() override;
		void printbits() override;
		void mutate(double p) override;

		uint64_t bits;

	private:
		friend class genetic_algorithm;
		void recombine(chromosome* partner) override;
		std::function<double(uint64_t)> & objective_function_;
		rng_engine & engine_;
	};
}