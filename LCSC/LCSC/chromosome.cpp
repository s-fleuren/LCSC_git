#include "stdafx.h"
#include "chromosome.hpp"

namespace lcsc {

	bitstring64::bitstring64(uint64_t genotype, std::function<double(uint64_t)>& objective_function, rng_engine& engine, 
		const int length, const int recombination_split) :
		objective_function_(objective_function), engine_(engine)
	{
		bits = genotype;
		length_ = length;
		selected_ = 0;
		recombination_split_ = recombination_split;
	}

	bitstring64::bitstring64(std::function<double(uint64_t)>& objective_function, rng_engine& engine, const int length, 
		int recombination_split) :
		objective_function_(objective_function), engine_(engine)
	{
		bits = engine.next_int(0, ((uint64_t)1 << length) - 1);
		length_ = length;
		selected_ = 0;
		recombination_split_ = recombination_split;
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

	void bitstring64::recombine(chromosome* partner)
	{
		auto bitstring_partner = dynamic_cast<bitstring64*>(partner);
		uint64_t bits1_right = bits;
		//Get rid of leftmost bits:
		bits1_right <<= length_ - recombination_split_;
		bits1_right >>= length_ - recombination_split_;

		uint64_t bits2_right = bitstring_partner->bits;
		//Get rid of leftmost bits:
		bits2_right <<= length_ - recombination_split_;
		bits2_right >>= length_ - recombination_split_;

		bits >>= recombination_split_;
		bits <<= recombination_split_;
		bits ^= bits2_right;

		bitstring_partner->bits >>= recombination_split_;
		bitstring_partner->bits <<= recombination_split_;
		bitstring_partner->bits ^= bits1_right;
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

	bitstring::bitstring(std::vector<uint64_t> genotype, std::function<double(std::vector<uint64_t>&)>& objective_function, 
		rng_engine& engine, const int length, const int recombination_split) :
		objective_function_(objective_function), engine_(engine), bits(genotype)
	{
		length_ = length;
		selected_ = 0;
		recombination_split_inner_ = recombination_split % 64;
		recombination_split_outer_ = (recombination_split >> 6);
		bits_size_ = bits.size();
		end_bits_length_ = length % 64;
	}

	double bitstring::objective_value()
	{
		return objective_function_(bits);
	}

	void bitstring::printbits()
	{
		uint64_t bit = (uint64_t)1 << (end_bits_length_ - 1);
		uint64_t bits_copy = bits.back();
		for (int i = end_bits_length_; i > 0; i--)
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
		for (int j = bits_size_ - 2; j >= 0; j--)
		{
			std::cout << " ";
			bit = (uint64_t)1 << 63;
			bits_copy = bits[j];
			for (int i = 64; i >= 0; i--)
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
		}
		std::cout << "\n";
	}

	void bitstring::recombine(chromosome* partner)
	{
		auto bitstring_partner = dynamic_cast<bitstring*>(partner);
		for (int i = 0; i < recombination_split_outer_; i++)
		{
			std::swap(bits[i], bitstring_partner->bits[i]);
		}
		uint64_t bits1_right = bits[recombination_split_outer_];
		//Get rid of leftmost bits:
		bits1_right <<= length_ - recombination_split_inner_;
		bits1_right >>= length_ - recombination_split_inner_;

		uint64_t bits2_right = bitstring_partner->bits[recombination_split_outer_];
		//Get rid of leftmost bits:
		bits2_right <<= length_ - recombination_split_inner_;
		bits2_right >>= length_ - recombination_split_inner_;;

		bits[recombination_split_outer_] >>= recombination_split_inner_;
		bits[recombination_split_outer_] <<= recombination_split_inner_;
		bits[recombination_split_outer_] ^= bits2_right;

		bitstring_partner->bits[recombination_split_outer_] >>= recombination_split_inner_;
		bitstring_partner->bits[recombination_split_outer_] <<= recombination_split_inner_;
		bitstring_partner->bits[recombination_split_outer_] ^= bits1_right;
	}

	void bitstring::mutate(double p)
	{
		uint64_t mutation_bits = 0;
		for (int j = 0; j < bits_size_ - 1; j++)
		{
			for (int i = 0; i < 64; i++)
			{
				mutation_bits <<= 1;
				if (engine_.next_double() < p)
				{
					mutation_bits++;
				}
			}
			bits[j] ^= mutation_bits;
		}
		mutation_bits = 0;
		for (int i = 0; i < end_bits_length_; i++)
		{
			mutation_bits <<= 1;
			if (engine_.next_double() < p)
			{
				mutation_bits++;
			}
		}
		bits.back() ^= mutation_bits;
	}
	void bitstring::clone(chromosome * other)
	{
		*this = *dynamic_cast<bitstring*>(other);
	}
	std::vector<uint64_t> random_bits_vector(int length, rng_engine& engine)
	{
		int output_size = (length >> 6) + 1;
		int end_bits_size = length % 64;
		auto output = std::vector<uint64_t>(output_size);
		for (int i = 0; i < output_size - 1; i++)
		{
			output[i] = engine.next_int(0, ((uint64_t)1 << 64) - 1);
		}
		output.back() = engine.next_int(0, ((uint64_t)1 << end_bits_size) - 1);
		return output;
	}
}