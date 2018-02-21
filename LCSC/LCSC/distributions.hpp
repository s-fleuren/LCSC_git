#pragma once

#include "rng.hpp"
#include <cstdint>

namespace lcsc {

	class uniform_int_distribution {
	public:
		uniform_int_distribution(rng_engine& engine, uint64_t min = 0,
			uint64_t max = 1000) :
			engine_(engine), min_(min), max_(max) {}
		uint64_t sample();

	private:
		rng_engine& engine_;
		uint64_t min_;
		uint64_t max_;
	};

	class uniform_real_distribution {
	public:
		uniform_real_distribution(const rng_engine& engine, double min = 0.0f,
			double max = 1.0f);
		double sample();
	};

	class normal_distribution {};
	class poisson_distribution {};
	class bernoulli_distribution {};
	class discrete_distribution {};

} // namespace lcsc
