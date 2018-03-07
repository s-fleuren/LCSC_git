#pragma once

#include <cstdint>

namespace lcsc {

	class rng_engine {
	public:
		virtual uint64_t next_int(uint64_t min, uint64_t max) = 0;
		virtual double next_double() = 0;
	};

	class lcrng : public rng_engine {
	public:
		lcrng(const uint64_t a, const uint64_t c, const uint64_t m, uint64_t seed) :
			a_(a), c_(c), m_(m), x_(seed) {
			if (a_ == 0)
			{
				printf("The value of a is not allowed to be 0. Press any key to exit.\n");
				getchar();
			}
			if (m_ == 0)
			{
				printf("The value of m is not allowed to be 0. Press any key to exit.\n");
				getchar();
			}
			if (((a_ * m_) /a_)/m_ != 1)
			{
				printf("Warning: a * m >= 2**64, integer overflow may occur.\n");
			}
		}

		uint64_t next_int(uint64_t min, uint64_t max) override;

		double next_double() override;

	private:
		const uint64_t a_;
		const uint64_t c_;
		const uint64_t m_;
		uint64_t x_;
	};

	class park_miller : public rng_engine {
	public:
		park_miller(uint64_t seed) :
			a_(16807), m_((1 << 31) - 1), x_(seed), q_(m_ / a_), r_(m_ % a_) {}

		uint64_t next_int(uint64_t min, uint64_t max) override;

		double next_double() override;

	private:
		const uint64_t a_;
		const uint64_t m_;
		uint64_t x_;
		const uint64_t q_;
		const uint64_t r_;
	};

	class xorshift : public rng_engine {
	public:
		xorshift(uint64_t seed) :
			x_(seed) {}

		uint64_t next_int(uint64_t min, uint64_t max) override;

		double next_double() override;

	private:
		uint64_t x_;

	};

} // namespace lcsc
