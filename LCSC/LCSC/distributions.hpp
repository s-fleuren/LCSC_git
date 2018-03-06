#pragma once

#include "rng.hpp"
#include <cstdint>

namespace lcsc {

	class uniform_int_distribution {
	public:
		uniform_int_distribution(rng_engine& engine, uint64_t min = 0,
			uint64_t max = 100) :
			engine_(engine), min_(min), max_(max) {}
		uint64_t sample();

	private:
		rng_engine & engine_;
		uint64_t min_;
		uint64_t max_;
	};

	class real_distribution {
	public:
		virtual double sample() = 0;
	};

	class uniform_real_distribution : public real_distribution {
	public:
		uniform_real_distribution(rng_engine& engine, double min = 0.0f,
			double max = 1.0f) :
			engine_(engine), min_(min), max_(max) {}
		double sample() override;

	private:
		rng_engine & engine_;
		double min_;
		double max_;
	};

	class exponential_distribution : public real_distribution{
	public:
		exponential_distribution(rng_engine& engine, double lambda = 1) :
			engine_(engine), lambda_(lambda) {}

		double sample() override;


	private:
		rng_engine & engine_;
		double lambda_;
	};

	class normal_distribution : public real_distribution {
	public:
		normal_distribution(rng_engine& engine, double mean = 0.0f,
			double sigma = 1.0f) :
			engine_(engine), exp_dis_(exponential_distribution(engine, 1)), mean_(mean), sigma_(sigma), 
			y1_(exp_dis_.sample()){}

		double sample() override;

	private:
		rng_engine & engine_;
		exponential_distribution exp_dis_;
		double mean_;
		double sigma_;
		double y1_;
	};

	class poisson_distribution {};
	class bernoulli_distribution {};
	class discrete_distribution {};

} // namespace lcsc
