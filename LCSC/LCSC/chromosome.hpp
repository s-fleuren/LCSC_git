#pragma once

#include <cstdint>
#include <utility>
#include <memory>

namespace lcsc {

	class chromosome {
	public:
		virtual double objective_value() = 0;
		virtual void printbits() = 0;
		virtual void mutate() = 0;

	protected:
		friend class genetic_algorithm;
		virtual void clone(chromosome* other) = 0;
		virtual void recombine(chromosome* partner) = 0;

		bool selected_;
		bool objective_value_computed_;
		double objective_value_;
	};

	class bitstring64 : public chromosome {
	public:
		class mutation_impl;
		class mutation_impl_uniform;
		class recombination_impl;
		class recombination_impl_one_point;
		class recombination_impl_uniform;

		bitstring64(uint64_t genotype, std::function<double(uint64_t)> & objective_function, rng_engine & engine, int length, 
			std::unique_ptr<mutation_impl> mutpimpl, std::unique_ptr<recombination_impl> recpimpl);
		bitstring64(std::function<double(uint64_t)> & objective_function, rng_engine & engine, const int length,
			std::unique_ptr<bitstring64::mutation_impl> mutpimpl, std::unique_ptr<recombination_impl> recpimpl);
		double objective_value() override;
		void printbits() override;
		void mutate() override;

		bitstring64& operator=(const bitstring64& other)
		{
			objective_function_ = other.objective_function_;
			engine_ = other.engine_;
			bits = other.bits;
			length_ = other.length_;
			selected_ = other.selected_;
			return *this;
		}

		uint64_t bits;


	protected:
		friend class genetic_algorithm;
		void recombine(chromosome* partner) override;
		void clone(chromosome* other) override;

		std::unique_ptr<mutation_impl> mutpimpl_;
		std::unique_ptr<recombination_impl> recpimpl_;

		std::function<double(uint64_t)>& objective_function_;
		rng_engine& engine_;
		int length_;
	};

	class bitstring : public chromosome {
	public:
		class mutation_impl;
		class mutation_impl_uniform;
		class recombination_impl;
		class recombination_impl_one_point;
		class recombination_impl_uniform;

		bitstring(std::vector<uint64_t> genotype, std::function<double(std::vector<uint64_t>&)>& objective_function, rng_engine & engine, 
			const int length, std::unique_ptr<bitstring::mutation_impl> mutpimpl, std::unique_ptr<bitstring::recombination_impl> recpimpl);

		double objective_value() override;
		void printbits() override;
		void mutate() override;

		bitstring& operator=(const bitstring& other)
		{
			for (int i = 0; i < bits_size_; i++)
			{
				bits[i] = other.bits[i];
			}
			selected_ = other.selected_;
			objective_value_computed_ = other.objective_value_computed_;
			return *this;
		}

		std::vector<uint64_t> bits;

	protected:
		friend class genetic_algorithm;
		void recombine(chromosome* partner) override;
		void clone(chromosome* other) override;

		std::unique_ptr<mutation_impl> mutpimpl_;
		std::unique_ptr<recombination_impl> recpimpl_;

		std::function<double(std::vector<uint64_t>&)>& objective_function_;
		rng_engine& engine_;
		int length_;
		size_t bits_size_;
		int end_bits_length_;
	};

	std::vector<uint64_t> random_bits_vector(int length, rng_engine& engine);
	std::vector<uint64_t> one_bits_vector(int length);
}