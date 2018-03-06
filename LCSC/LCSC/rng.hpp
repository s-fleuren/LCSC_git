#pragma once

#include <cstdint>

namespace lcsc {

	class rng_engine {
	public:
		virtual uint64_t next_int(uint64_t min, uint64_t max) = 0;
		virtual double next() = 0;
	};

	class lcrng : public rng_engine {
	public:
		lcrng(const int a, const int c, const int m, uint64_t seed) :
			a_(a), c_(c), m_(m), x_(seed) {}

		uint64_t next_int(uint64_t min, uint64_t max) override;

		double next() override;

	private:
		int a_;
		int c_;
		int m_;
		uint64_t x_;
	};

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
