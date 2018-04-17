#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>
#include <math.h>
#include <functional>


namespace lcsc {

	class haltonSequence
	{
	public:
		haltonSequence(std::vector<uint64_t> &primes, int d, int length);
		std::vector<double> halton(int n);
		std::function<double(int)> haltonDoubleForExtern();


	private:
		std::vector<std::vector<double>> haltonSequence_;
		std::vector<uint64_t> & primes_;
		int d_;
		int length_;
		double haltonDouble(int n);
	};

	std::vector<uint64_t> primeVector(int length);

	std::vector<double> haltonCompute(std::vector<uint64_t> &primes, int d, int n);

	int highestOneBit(uint64_t i);


} // namespace lcsc
