#pragma once

#include "rng.hpp"
#include <cstdint>

namespace lcsc {

	class histogram {
	public:
		histogram(rng_engine& engine, const uint64_t M) :
		engine_(engine), M_(M) {}
		
		void test(const uint64_t n);

	private:
		rng_engine& engine_;
		const uint64_t M_;
	};
}