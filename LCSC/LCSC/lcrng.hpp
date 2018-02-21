#pragma once

#include "rng.hpp"
#include <cstdint>

namespace lcsc {

	class lcrng : public rng_engine {
	public:
		lcrng(const int a, const int c, const int m, uint64_t seed) :
			a_(a), c_(c), m_(m), x_(seed) {}

		double next() override;

	private:
		int a_;
		int c_;
		int m_;
		uint64_t x_;


	};

} // namespace lcsc
