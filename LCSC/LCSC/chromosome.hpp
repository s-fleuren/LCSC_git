#pragma once

#include <cstdint>
#include <utility>

namespace lcsc {

	class chromosome {
	public:
		virtual double objective_value() = 0;
		virtual void printbits() = 0;
		virtual void mutate(double p) = 0;

	protected:
		friend class genetic_algorithm;
		virtual void clone(chromosome* other) = 0;
		virtual void recombine(chromosome* partner) = 0;

		bool selected_;
	};

	class bitstring64 : public chromosome {
	public:
		bitstring64(uint64_t genotype, std::function<double(uint64_t)> & objective_function, rng_engine & engine, const int length, int recombination_split);
		bitstring64(std::function<double(uint64_t)> & objective_function, rng_engine & engine, const int length, int recombination_split);
		double objective_value() override;
		void printbits() override;
		void mutate(double p) override;

		//copy constructors
		//bitstring64(const bitstring64& other) : 
		//	objective_function_(other.objective_function_), engine_(other.engine_), bits(other.bits) {}
		bitstring64& operator=(const bitstring64& other)
		{
			objective_function_ = other.objective_function_;
			engine_ = other.engine_;
			bits = other.bits;
			length_ = other.length_;
			recombination_split_ = other.recombination_split_;
			selected_ = other.selected_;
			return *this;
		}

		uint64_t bits;

	private:
		friend class genetic_algorithm;
		void recombine(chromosome* partner) override;
		void clone(chromosome* other) override;

		std::function<double(uint64_t)>& objective_function_;
		rng_engine& engine_;
		int length_;
		int recombination_split_;
	};

	class bitstring : public chromosome {
	public:
		bitstring(std::vector<uint64_t> genotype, std::function<double(std::vector<uint64_t>&)>& objective_function, rng_engine & engine, 
			const int length, int recombination_split);

		double objective_value() override;
		void printbits() override;
		void mutate(double p) override;

		bitstring& operator=(const bitstring& other)
		{
			objective_function_ = other.objective_function_;
			engine_ = other.engine_;
			for (int i = 0; i < bits_size_; i++)
			{
				bits[i] = other.bits[i];
			}
			length_ = other.length_;
			recombination_split_inner_ = other.recombination_split_inner_;
			recombination_split_outer_ = other.recombination_split_outer_;
			selected_ = other.selected_;
			bits_size_ = other.bits_size_;
			end_bits_length_ = other.end_bits_length_;
			return *this;
		}

		std::vector<uint64_t> bits;

	private:
		friend class genetic_algorithm;
		void recombine(chromosome* partner) override;
		void clone(chromosome* other) override;

		std::function<double(std::vector<uint64_t>&)>& objective_function_;
		rng_engine& engine_;
		int length_;
		int recombination_split_inner_;
		int recombination_split_outer_;
		size_t bits_size_;
		int end_bits_length_;
	};

	std::vector<uint64_t> random_bits_vector(int length, rng_engine& engine);
}