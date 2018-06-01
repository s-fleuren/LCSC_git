#include "stdafx.h"

namespace lcsc {
	bitstring64::recombination_impl_one_point::recombination_impl_one_point(int crossover_point) {
		crossover_point_ = crossover_point;
	}

	void bitstring64::recombination_impl_one_point::recombine(bitstring64& b, bitstring64& c) {
		uint64_t bits1_right = b.bits;
		//Get rid of leftmost bits:
		bits1_right <<= 64 - crossover_point_;
		bits1_right >>= 64 - crossover_point_;

		uint64_t bits2_right = c.bits;
		//Get rid of leftmost bits:
		bits2_right <<= 64 - crossover_point_;
		bits2_right >>= 64 - crossover_point_;

		b.bits >>= crossover_point_;
		b.bits <<= crossover_point_;
		b.bits ^= bits2_right;

		c.bits >>= crossover_point_;
		c.bits <<= crossover_point_;
		c.bits ^= bits1_right;
	}

	bitstring64::recombination_impl_uniform::recombination_impl_uniform() {}

	void bitstring64::recombination_impl_uniform::recombine(bitstring64& b, bitstring64& c) {
		uint64_t crossover_points = b.engine_.next_int(0, -1);
		uint64_t crossover_inverse = -1 - crossover_points;
		uint64_t bits1 = b.bits && crossover_points;
		uint64_t bits2 = c.bits && crossover_inverse;
		uint64_t child = bits1 || bits2;
		b.bits ^= child ^ c.bits;
		c.bits = child;
	}

	bitstring::recombination_impl_one_point::recombination_impl_one_point(int crossover_point) {
		crossover_point_inner_ = crossover_point % 64;
		crossover_point_outer_ = (crossover_point >> 6);
	}

	void bitstring::recombination_impl_one_point::recombine(bitstring& b, bitstring& c) {
		for (int i = 0; i < crossover_point_outer_; i++)
		{
			std::swap(b.bits[i], c.bits[i]);
		}
		if (crossover_point_inner_ != 0)
		{
			return;
			uint64_t bits1_right = b.bits[crossover_point_outer_];
			//Get rid of leftmost bits:
			bits1_right <<= 64 - crossover_point_inner_;
			bits1_right >>= 64 - crossover_point_inner_;

			uint64_t bits2_right = c.bits[crossover_point_outer_];
			//Get rid of leftmost bits:
			bits2_right <<= 64 - crossover_point_inner_;
			bits2_right >>= 64 - crossover_point_inner_;

			b.bits[crossover_point_outer_] >>= crossover_point_inner_;
			b.bits[crossover_point_outer_] <<= crossover_point_inner_;
			b.bits[crossover_point_outer_] ^= bits2_right;

			c.bits[crossover_point_outer_] >>= crossover_point_inner_;
			c.bits[crossover_point_outer_] <<= crossover_point_inner_;
			c.bits[crossover_point_outer_] ^= bits1_right;
		}
	}

	bitstring::recombination_impl_uniform::recombination_impl_uniform() {}

	void bitstring::recombination_impl_uniform::recombine(bitstring& b, bitstring& c) {
		for (int i = 0; i < b.bits_size_; i++)
		{
			uint64_t crossover_points = b.engine_.next_int(0, -1);
			uint64_t crossover_inverse = -1 - crossover_points;
			uint64_t bits1 = b.bits[i] & crossover_points;
			uint64_t bits2 = c.bits[i] & crossover_inverse;
			uint64_t child = bits1 | bits2;
			b.bits[i] ^= child ^ c.bits[i];
			c.bits[i] = child;
		}
	}
}