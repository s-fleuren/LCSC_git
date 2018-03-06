#pragma once

#include "rng.hpp"
#include <cstdint>

namespace lcsc {

	class xorshift : public rng_engine {
	public:
		xorshift(uint64_t seed) :
			x_(seed) {}

		uint64_t next_int(uint64_t min, uint64_t max) override;

		double next() override;

	private:
		uint64_t x_;

	};

} // namespace lcsc