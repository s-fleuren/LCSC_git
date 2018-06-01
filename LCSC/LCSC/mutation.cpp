#include "stdafx.h"

namespace lcsc {

	bitstring64::mutation_impl_uniform::mutation_impl_uniform(double p) {
		mutation_chance_ = p;
	}

	void bitstring64::mutation_impl_uniform::mutate(bitstring64& b) {
		uint64_t mutation_bits = 0;
		for (int i = 0; i < b.length_; i++)
		{
			mutation_bits <<= 1;
			if (b.engine_.next_double() < mutation_chance_)
			{
				mutation_bits++;
			}
		}
		b.bits ^= mutation_bits;
	}

	bitstring::mutation_impl_uniform::mutation_impl_uniform(double p) {
		mutation_chance_ = p;
	}

	void bitstring::mutation_impl_uniform::mutate(bitstring& b) {
		uint64_t mutation_bits = 0;
		for (int j = 0; j < b.bits_size_ - 1; j++)
		{
			for (int i = 0; i < 64; i++)
			{
				mutation_bits <<= 1;
				if (b.engine_.next_double() < 0.1)
				{
					mutation_bits++;
				}
			}
			b.bits[j] ^= mutation_bits;
		}
		mutation_bits = 0;
		for (int i = 0; i < b.end_bits_length_; i++)
		{
			mutation_bits <<= 1;
			if (b.engine_.next_double() < 0.1)
			{
				mutation_bits++;
			}
		}
		b.bits.back() ^= mutation_bits;
	}
}