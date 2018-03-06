#pragma once

#include <cstdint>

namespace lcsc {

	class rng_engine {
	public:
		virtual uint64_t next_int(uint64_t min, uint64_t max) = 0;
		virtual double next() = 0;
	};

} // namespace lcsc
