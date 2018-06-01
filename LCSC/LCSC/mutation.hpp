#pragma once

namespace lcsc
{
	class bitstring64::mutation_impl {
	public:
		virtual void mutate(bitstring64& b) = 0;
	};

	class bitstring64::mutation_impl_uniform : public bitstring64::mutation_impl {
	public:
		mutation_impl_uniform(double p);
		void mutate(bitstring64& b) override;

	private:
		double mutation_chance_;
	};

	class bitstring::mutation_impl {
	public:
		virtual void mutate(bitstring& b) = 0;
	};

	class bitstring::mutation_impl_uniform : public bitstring::mutation_impl {
	public:
		mutation_impl_uniform(double p);
		void mutate(bitstring& b) override;

	private:
		double mutation_chance_;
	};
}