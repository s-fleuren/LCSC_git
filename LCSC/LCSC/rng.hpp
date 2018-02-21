#pragma once

#include <cstdint>

namespace lcsc {

	class rng_engine {
	public:
		virtual double next() = 0;
	};

} // namespace lcsc
