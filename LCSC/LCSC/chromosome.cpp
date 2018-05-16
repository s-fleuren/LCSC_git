#include "stdafx.h"
#include "chromosome.hpp"

namespace lcsc {

	bitstring64::bitstring64(uint64_t genotype, std::function<double(uint64_t)>& objective_function, rng_engine& engine, 
		const int length) :
		objective_function_(objective_function), engine_(engine)
	{
		bits = genotype;
		length_ = length;
		selected = 0;
	}

	bitstring64::bitstring64(std::function<double(uint64_t)>& objective_function, rng_engine& engine, const int length) :
		objective_function_(objective_function), engine_(engine)
	{
		bits = engine.next_int(0, ((uint64_t)1 << length) - 1);
		length_ = length;
		selected = 0;
	}

	double bitstring64::objective_value()
	{
		return objective_function_(bits);
	}

	void bitstring64::printbits()
	{
		uint64_t bit = (uint64_t)1 << length_;
		uint64_t bits_copy = bits;
		for (int i = length_; i >= 0; i--)
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

	std::pair<chromosome, chromosome> bitstring64::recombine(chromosome* partner, int crossover_point)
	{
		auto bitstring_partner = dynamic_cast<bitstring64*>(partner);
		uint64_t bits1_right = bits;
		//Get rid of leftmost bits:
		bits1_right <<= length_ - crossover_point;
		bits1_right >>= length_ - crossover_point;

		uint64_t bits1_left = bits;
		bits1_left >>= crossover_point;
		bits1_left <<= crossover_point;

		uint64_t bits2_right = bitstring_partner->bits;
		//Get rid of leftmost bits:
		bits2_right <<= length_ - crossover_point;
		bits2_right >>= length_ - crossover_point;

		uint64_t bits2_left = bitstring_partner->bits;
		bits2_left >>= crossover_point;
		bits2_left <<= crossover_point;

		return std::make_pair<chromosome, chromosome>(
			bitstring64(bits1_left + bits2_right, this->objective_function_, this->engine_, this->length_), 
			bitstring64(bits2_left + bits1_right, this->objective_function_, this->engine_, this->length_));
	}

	void bitstring64::mutate(double p)
	{
		uint64_t mutation_bits = 0;
		for (int i = 0; i < length_; i++)
		{
			mutation_bits <<= 1;
			if (engine_.next_double() < p)
			{
				mutation_bits++;
			}
		}
		bits ^= mutation_bits;
	}
	void bitstring64::clone(chromosome * other)
	{
		*this = *dynamic_cast<bitstring64*>(other);
	}
}