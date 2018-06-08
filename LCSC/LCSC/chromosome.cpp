#include "stdafx.h"

namespace lcsc {

	bitstring64::bitstring64(uint64_t genotype, std::function<double(uint64_t)>& objective_function, rng_engine& engine,
		int length, std::unique_ptr<bitstring64::mutation_impl> mutpimpl, std::unique_ptr<recombination_impl> recpimpl) :
		objective_function_(objective_function), engine_(engine)
	{
		bits = genotype;
		length_ = length;
		mutpimpl_ = std::move(mutpimpl);
		recpimpl_ = std::move(recpimpl);
		selected_ = 0;
		objective_value_computed_ = false;
		objective_value_ = 0;
	}

	bitstring64::bitstring64(std::function<double(uint64_t)>& objective_function, rng_engine& engine, const int length,
		std::unique_ptr<bitstring64::mutation_impl> mutpimpl, std::unique_ptr<recombination_impl> recpimpl) :
		objective_function_(objective_function), engine_(engine)
	{
		bits = engine.next_int(0, ((uint64_t)1 << length) - 1);
		length_ = length;
		mutpimpl_ = std::move(mutpimpl);
		recpimpl_ = std::move(recpimpl);
		selected_ = 0;
		objective_value_computed_ = false;
		objective_value_ = 0;
	}

	double bitstring64::objective_value()
	{
		if (!objective_value_computed_)
		{
			objective_value_ = objective_function_(bits);
			objective_value_computed_ = true;
		}
		return objective_value_;
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
		bitstring64* bitstring_partner = dynamic_cast<bitstring64*>(partner);

		objective_value_computed_ = false;
		bitstring_partner->objective_value_computed_ = false;

		recpimpl_->recombine(*this, *bitstring_partner);
	}

	void bitstring64::mutate()
	{
		objective_value_computed_ = false;
		mutpimpl_->mutate(*this);
	}

	void bitstring64::clone(chromosome* other)
	{
		*this = *dynamic_cast<bitstring64*>(other);
	}

	bitstring::bitstring(std::vector<uint64_t> genotype, std::function<double(std::vector<uint64_t>&)>& objective_function,
		rng_engine& engine, int length, std::unique_ptr<bitstring::mutation_impl> mutpimpl, 
		std::unique_ptr<bitstring::recombination_impl> recpimpl) :
		objective_function_(objective_function), engine_(engine), bits(genotype)
	{
		length_ = length;
		mutpimpl_ = std::move(mutpimpl);
		recpimpl_ = std::move(recpimpl);
		selected_ = 0;
		objective_value_computed_ = false;
		objective_value_ = 0;
		bits_size_ = bits.size();
		end_bits_length_ = length % 64;
	}

	double bitstring::objective_value()
	{
		if (!objective_value_computed_)
		{
			objective_value_ = objective_function_(bits);
			objective_value_computed_ = true;
		}
		return objective_value_;
	}

	void bitstring::printbits()
	{
		uint64_t bit = (uint64_t)1 << (end_bits_length_ - 1);
		uint64_t bits_copy = bits.back();
		if (end_bits_length_ > 0)
		{
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
			std::cout << " ";
		}
		for (int j = bits_size_ - 2; j >= 0; j--)
		{
			bit = (uint64_t)1 << 63;
			bits_copy = bits[j];
			for (int i = 64; i > 0; i--)
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
			std::cout << " ";
		}
		std::cout << "\n";
	}

	void bitstring::recombine(chromosome* partner)
	{
		auto bitstring_partner = dynamic_cast<bitstring*>(partner);

		objective_value_computed_ = false;
		bitstring_partner->objective_value_computed_ = false;

		recpimpl_->recombine(*this, *bitstring_partner);
	}

	void bitstring::mutate()
	{
		objective_value_computed_ = false;
		mutpimpl_->mutate(*this);
	}

	void bitstring::clone(chromosome* other)
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
			output[i] = engine.next_int(0, -1);
		}
		output.back() = engine.next_int(0, ((uint64_t)1 << end_bits_size) - 1);
		return output;
	}

	std::vector<uint64_t> one_bits_vector(int length)
	{
		int output_size = (length >> 6) + 1;
		int end_bits_size = length % 64;
		auto output = std::vector<uint64_t>(output_size);
		for (int i = 0; i < output_size - 1; i++)
		{
			output[i] = -1;
		}
		output.back() = ((uint64_t)1 << end_bits_size) - 1;
		return output;
	}
}