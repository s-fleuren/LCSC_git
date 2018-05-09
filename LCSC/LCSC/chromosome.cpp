#include "stdafx.h"
#include "chromosome.hpp"

namespace lcsc {

	bitstring64::bitstring64(uint64_t genotype, std::function<double(uint64_t)> & objective_function, rng_engine & engine) :
		objective_function_(objective_function), engine_(engine)
	{
		bits = genotype;
	}

	bitstring64::bitstring64(std::function<double(uint64_t)>& objective_function, rng_engine & engine) :
		objective_function_(objective_function), engine_(engine)
	{
		bits = engine.next_int(0, ((uint64_t)1 << 63) - 1);
	}

	double bitstring64::objective_value()
	{
		return objective_function_(bits);
	}

	void bitstring64::printbits()
	{
		uint64_t bit = (uint64_t)1 << 63;
		uint64_t bits_copy = bits;
		for (int i = 63; i >= 0; i--)
		{
			if (bit <= bits_copy)
			{
				std::cout << 1;
				bits_copy -= bit;
			}
			else
			{
				std::cout << 0;
			}
			bit >>= 1;
		}
		std::cout << "\n";
	}

	void bitstring64::recombine(chromosome* partner)
	{
		auto bitstring_partner = dynamic_cast<bitstring64*>(partner);
		uint64_t bits1_right = bits;
		//Get rid of leftmost bits:
		bits1_right <<= 32;
		bits1_right >>= 32;

		uint64_t bits2_right = bitstring_partner->bits;
		//Get rid of leftmost bits:
		bits2_right <<= 32;
		bits2_right >>= 32;

		bits >>= 32;
		bits <<= 32;
		bits += bits2_right;

		bitstring_partner->bits >>= 32;
		bitstring_partner->bits <<= 32;
		bitstring_partner->bits += bits1_right;
	}

	void bitstring64::mutate(double p)
	{
		uint64_t mutation_bits = 0;
		for (int i = 0; i < 64; i++)
		{
			mutation_bits <<= 1;
			if (engine_.next_double() < p)
			{
				mutation_bits++;
			}
		}
		bits ^= mutation_bits;
	}
}