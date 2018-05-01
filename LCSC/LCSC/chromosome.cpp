#include "stdafx.h"
#include "chromosome.hpp"

namespace lcsc {

	bitstring64::bitstring64(uint64_t genotype, std::function<double(uint64_t)> & objective_function, rng_engine & engine) :
		objective_function_(objective_function), engine_(engine)
	{
		bits = genotype;
	}

	double bitstring64::objective_value()
	{
		return objective_function_(bits);
	}

	void bitstring64::mutate(double p)
	{
		uint64_t mutation_bits = 0;
		if (engine_.next_double() < p)
		{
			mutation_bits++;
		}
		for (int i = 0; i < 64; i++)
		{
			mutation_bits << 1;
			if (engine_.next_double() < p)
			{
				mutation_bits++;
			}
		}
		bits ^= mutation_bits;
	}

	std::pair<chromosome, chromosome> bitstring64::recombine(chromosome & partner)
	{
		if (typeid(partner) == typeid(this))
		{
			auto output = std::make_pair(bits, partner.bits);
		}
	}
}
