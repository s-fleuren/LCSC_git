#pragma once

namespace lcsc
{
	class bitstring64::recombination_impl {
	public:
		virtual void recombine(bitstring64& b, bitstring64& c) = 0;
	};

	class bitstring64::recombination_impl_one_point : public bitstring64::recombination_impl {
	public:
		recombination_impl_one_point(int crossover_point);
		void recombine(bitstring64& b, bitstring64& c) override;

	private:
		int crossover_point_;
	};

	class bitstring64::recombination_impl_uniform : public bitstring64::recombination_impl {
	public:
		recombination_impl_uniform();
		void recombine(bitstring64& b, bitstring64& c) override;
	};

	class bitstring::recombination_impl {
	public:
		virtual void recombine(bitstring& b, bitstring& c) = 0;
	};

	class bitstring::recombination_impl_one_point : public bitstring::recombination_impl {
	public:
		recombination_impl_one_point(int crossover_point);
		void recombine(bitstring& b, bitstring& c) override;

	private:
		int crossover_point_inner_;
		int crossover_point_outer_;
	};

	class bitstring::recombination_impl_uniform : public bitstring::recombination_impl {
	public:
		recombination_impl_uniform();
		void recombine(bitstring& b, bitstring& c) override;
	};
}